#include "game.h"
#include <QDebug>

namespace NAGE
{
    Game::Game(FpsLimit _limit)
        : IGame(_limit),
          skyboxShader(nullptr),
          skybox(nullptr),
          lampShader(nullptr),
          lamp(nullptr),
          lampTransform(nullptr),
          sun(nullptr),
          blendmap(nullptr),
          terrainTexture1(nullptr),
          terrainTexture2(nullptr),
          terrainTexture3(nullptr),
          terrainTexture4(nullptr),
          heightMap(nullptr),
          cdlodTerrain(nullptr),
          cdlodWater(nullptr),
          waterHeightmap(nullptr)
    {

    }

    Game::~Game()
    {
        delete skyboxShader;
        delete skybox;
        delete lampShader;
        delete lamp;
        delete lampTransform;
        delete sun;
        delete blendmap;
        delete terrainTexture1;
        delete terrainTexture2;
        delete terrainTexture3;
        delete terrainTexture4;
        delete heightMap;
        delete cdlodTerrain;
        delete waterHeightmap;
        delete cdlodWater;
    }

    void Game::initializeScene()
    {
        /* Heightmap noise examples
        HeightMap heightMap;
        heightMap.setScale(5);
        FPerlinNoise::OctaveSettings settings;
        settings.frequency = 0.0009f;
        settings.persistence = 0.3f;
        settings.octaves = 15;
        settings.amplitude = 10.0f;
        heightMap.perlinNoise(1024, 1024, 21412312, settings);
        heightMap.diamondSquare(1025, 1025);
        //heightMap.flat(512, 512);*/

        // Skybox
        skyboxShader = new Shader;
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
             "../src/engine/shader/cubemapSkybox.vert");
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/cubemapSkybox.frag");
        skyboxShader->link();

        std::vector<std::string> skyboxFaces = {
            "../resources/texture/skybox/3/left.jpg",
            "../resources/texture/skybox/3/right.jpg",
            "../resources/texture/skybox/3/top.jpg",
            "../resources/texture/skybox/3/bottom.jpg",
            "../resources/texture/skybox/3/front.jpg",
            "../resources/texture/skybox/3/back.jpg",
        };

        skybox = new Skybox(skyboxShader);
        skybox->addFacesTextures(skyboxFaces);
        sceneManager()->sceneByKey("editor")->addToScene(skybox);

        // Lamp
        lampShader = new Shader;
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lamp.vert");
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lamp.frag");
        lampShader->link();

        Sphere sphere;
        Mesh mesh(sphere.vertices(), sphere.indices());
        lamp = new PointLight(mesh.vertices(), mesh.indices());
        lamp->setShader(lampShader);

        lampTransform = new Transform;
        lampTransform->setTranslation(200.0f, 80.0f, 135.0f);
        lampTransform->scale(2.0f);

        lamp->setTransformation(lampTransform);
        lamp->setId(0);
        lamp->setColor(Color(255.0f, 0.0f, 0.0f));
        lamp->setAttenuation(1.0f, 0.05f, 0.002f);
        sceneManager()->sceneByKey("editor")->addToScene("lamp", lamp);

        // Sun
        sun = new Sun;
        sun->setLightDirection(Vector3f(-0.2f, -1.0f, -1.3f));
        sceneManager()->sceneByKey("editor")->addToScene(sun);

        /*cubeShader = new Shader;
        cubeShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lighting.vert");
        cubeShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lighting.frag");
        cubeShader->link();

        cubeMesh = new Mesh("../resources/model/cube.obj");
        diffCube = new Texture("../resources/texture/container.png", TextureType::TEXTURE_2D);
        specCube = new Texture("../resources/texture/container_specular.png", TextureType::TEXTURE_2D);
        cubeMesh->addTexture(diffCube);
        cubeMesh->addTexture(specCube);

        material = new Material;
        material->setAmbient(0.2f, 0.2f, 0.2f);
        material->setDiffuse(0.5f, 0.5f, 0.5f);
        material->setSpecular(1.0f, 1.0f, 1.0f);
        material->setShininess(64.0f);
        material->setDiffuseTexture(0);
        material->setSpecularTexture(1);
        material->useTextures(cubeShader);
        cubeMesh->setMaterial(material);

        cubeTransform = new Transform;
        cubeTransform->setTranslation(210.0f, 35.0f, 140.0f);
        cubeTransform->setScale(3.0f);

        cubeModel = new Model;
        cubeModel->addMesh(cubeMesh);
        cubeModel->setTransformation(cubeTransform);
        cubeModel->setShader(cubeShader);
        sceneManager()->sceneByKey("editor")->addToScene("cube", cubeModel);*/

        // CDLOD terrain
        heightMap = new HeightMap;
        heightMap->loadFromFile("../resources/texture/terrain/heightmap1.jpg");
        //heightMap->perlinNoise(1024, 1024, 12345);
        //heightMap->diamondSquare(1025, 1025);
        //heightMap->flat(1024, 1024);

        blendmap = new Texture("../resources/texture/terrain/blendmap1.jpg", TextureType::TEXTURE_2D);
        terrainTexture1 = new Texture("../resources/texture/terrain/dirt.jpg", TextureType::TEXTURE_2D);
        terrainTexture2 = new Texture("../resources/texture/terrain/grass.jpg", TextureType::TEXTURE_2D);
        terrainTexture3 = new Texture("../resources/texture/terrain/stone.jpg", TextureType::TEXTURE_2D);
        terrainTexture4 = new Texture("../resources/texture/terrain/snow.jpg", TextureType::TEXTURE_2D);

        cdlodTerrain = new CDLODTerrain(8, heightMap);
        cdlodTerrain->addTexture("material.blendmap", blendmap);
        cdlodTerrain->addTexture("material.dirt", terrainTexture1);
        cdlodTerrain->addTexture("material.grass", terrainTexture2);
        cdlodTerrain->addTexture("material.stone", terrainTexture3);
        cdlodTerrain->addTexture("material.snow", terrainTexture4);
        cdlodTerrain->useHeightMapTexture(cdlodTerrain->shader());
        sceneManager()->sceneByKey("editor")->addToScene(cdlodTerrain);

        // CDLOD water
        waterHeightmap = new HeightMap;
        waterHeightmap->flat(4096, 4096);

        Transform* waterTransform = new Transform;
        waterTransform->setTranslation(0.0f, 20.0f, 0.0f);

        CDLODSettings waterLodSettings;
        waterLodSettings.gridResolution = 16;

        cdlodWater = new CDLODWater(8, waterHeightmap, waterLodSettings);
        cdlodWater->useHeightMapTexture(cdlodWater->shader());
        cdlodWater->setTransformation(waterTransform);
        sceneManager()->sceneByKey("editor")->addToScene(cdlodWater);
    }
}
