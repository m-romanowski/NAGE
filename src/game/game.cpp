#include "game.h"
#include <QDebug>

namespace NAGE
{
    Game::Game(FpsLimit _limit)
        : IGame(_limit)
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
        delete terrainMaterial;
        delete terrainTexture1;
        delete terrainShader;
        delete heightMap;
        delete cdlodTerrain;
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
        lampTransform->setTranslation(200.0f, 50.0f, 135.0f);
        lampTransform->scale(2.0f);

        lamp->setTransformation(lampTransform);
        lamp->setId(0);
        lamp->setColor(Color(255.0f, 3.0f, 3.0f));
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
        terrainShader = new Shader;
        terrainShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/cdlodterrain.vert");
        terrainShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/cdlodterrain.frag");
        terrainShader->link();

        terrainTexture1 = new Texture("../resources/texture/terrain.png", TextureType::TEXTURE_2D);
        terrainShader->use();
        terrainShader->setInt("material.grass", 0);

        terrainMaterial = new Material;
        terrainMaterial->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        terrainMaterial->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        terrainMaterial->setSpecular(Vector3f(0.05f, 0.05f, 0.05f));
        terrainMaterial->setShininess(32.0f);

        heightMap = new HeightMap;
        heightMap->loadFromFile("/home/inc/Downloads/heightmap.jpg");

        cdlodTerrain = new CDLODTerrain(8, heightMap);
        cdlodTerrain->addTexture(terrainTexture1);
        cdlodTerrain->setMaterial(terrainMaterial);
        cdlodTerrain->setShader(terrainShader);
        cdlodTerrain->useHeightMapTexture();
        sceneManager()->sceneByKey("editor")->addToScene(cdlodTerrain);
    }
}
