#include "game.h"

namespace NAGE
{
    Game::Game(FpsLimit _limit)
        : IGame(_limit)
    {

    }

    void Game::initializeScene()
    {
        // Skybox
        skyboxShader = std::make_shared<Shader>();
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
             "../src/engine/shader/cubemapSkybox.vert");
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/cubemapSkybox.frag");
        skyboxShader->link();

        std::vector<std::string> skyboxFaces = {
            "../resources/texture/skybox/2/right.jpg",
            "../resources/texture/skybox/2/left.jpg",
            "../resources/texture/skybox/2/top.jpg",
            "../resources/texture/skybox/2/bottom.jpg",
            "../resources/texture/skybox/2/front.jpg",
            "../resources/texture/skybox/2/back.jpg",
        };

        skybox = std::make_shared<Skybox>(skyboxShader.get());
        skybox->addFacesTextures(skyboxFaces);
        sceneManager()->sceneByKey("editor")->addToScene(skybox.get());

        // Lamp
        Sphere sphere;

        lampTransform = std::make_shared<Transform>();
        lampTransform->setTranslation(430.0f, 50.0f, 455.0f);
        lampTransform->scale(2.0f);

        lampShader = std::make_shared<Shader>();
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lamp.vert");
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lamp.frag");
        lampShader->link();
        lampShader->use();
        lampShader->setFloat("expand", 0.25f);
        lampShader->setVec2("center", lampTransform->translation().x(), lampTransform->translation().y());
        lampShader->setFloat("radius", sphere.radius());
        lampShader->setFloat("windowHeight", IWindow::currentWindowSize().y());

        Mesh mesh(sphere.vertices(), sphere.indices());
        lamp = std::make_shared<PointLight>(mesh.vertices(), mesh.indices());
        lamp->setShader(lampShader.get());

        lamp->setTransformation(lampTransform.get());
        lamp->setId(0);
        lamp->setColor(Color(255.0f, 0.0f, 0.0f));
        lamp->setAttenuation(1.0f, 0.05f, 0.002f);

        sceneManager()->sceneByKey("editor")->addToScene("lamp", lamp.get());

        // Sun
        sun = std::make_shared<Sun>();
        sun->setGradientExpand(0.25f);
        sun->setLightDirection(Vector3f(-0.2f, -1.0f, -1.3f));
        sceneManager()->sceneByKey("editor")->addToScene(sun.get());

        // CDLOD water
        waterHeightmap = std::make_shared<HeightMap>();
        waterHeightmap->flat(4096, 4096);

        Transform* waterTransform = new Transform;
        waterTransform->setTranslation(0.0f, 40.0f, 0.0f);

        CDLODSettings waterLodSettings;
        waterLodSettings.gridResolution_ = 16;

        cdlodWater = std::make_shared<CDLODWater>(8, waterHeightmap.get(), waterLodSettings);
        cdlodWater->setWaveNoiseFactor(120.0f);
        // cdlodWater->setupFlowMapEffect(256, 256);
        cdlodWater->setWaveFrequency(0.1f);
        cdlodWater->setHeightMapProperties(cdlodWater->shader());
        cdlodWater->setTransformation(waterTransform);
        sceneManager()->sceneByKey("editor")->addToScene(cdlodWater.get());

        sceneManager()->sceneByKey("editor")->camera()->translate(80.0f, 50.0f, 100.0f);

        // CDLOD terrain
        heightMap = std::make_shared<HeightMap>();
        heightMap->loadFromFile("../resources/texture/terrain/heightmap1_2k.jpg");

        blendmap = std::make_shared<Texture>("../resources/texture/terrain/blendmap1_2k.jpg", TextureType::TEXTURE_2D);
        terrainTexture1 = std::make_shared<Texture>("../resources/texture/terrain/dirt.jpg", TextureType::TEXTURE_2D);
        terrainTexture2 = std::make_shared<Texture>("../resources/texture/terrain/grass.jpg", TextureType::TEXTURE_2D);
        terrainTexture3 = std::make_shared<Texture>("../resources/texture/terrain/stone.jpg", TextureType::TEXTURE_2D);
        terrainTexture4 = std::make_shared<Texture>("../resources/texture/terrain/snow.jpg", TextureType::TEXTURE_2D);

        cdlodTerrain = std::make_shared<CDLODTerrain>(8, heightMap.get());

        cdlodTerrain->addTexture("material.blendmap", blendmap.get());
        cdlodTerrain->addTexture("material.dirt", terrainTexture1.get());
        cdlodTerrain->addTexture("material.grass", terrainTexture2.get());
        cdlodTerrain->addTexture("material.stone", terrainTexture3.get());
        cdlodTerrain->addTexture("material.snow", terrainTexture4.get());
        cdlodTerrain->setHeightMapProperties(cdlodTerrain->shader());

        sceneManager()->sceneByKey("editor")->addToScene(cdlodTerrain.get());
    }
}
