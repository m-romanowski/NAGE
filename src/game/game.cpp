#include "game.h"

namespace NAGE
{
    Game::Game(FpsLimit _limit)
        : IGame(_limit)
    {

    }

    Game::~Game()
    {
        delete diff;
        delete spec;

        delete lampShader;
        delete skyboxShader;
        delete lightingShader;
        delete terrainShader;

        delete material;
        delete terrainMaterial;
        delete transform;
        delete cubeTransform;

        delete mesh;
        delete cubeModel;
        delete lamp;
        delete sun;
        delete skybox;
        delete terrain;
    }

    void Game::initializeScene()
    {
        // Add terrain.
        diff = new Texture("../resources/texture/terrain.png", TextureType::TEXTURE_2D);

        terrainMaterial = new Material;
        terrainMaterial->setAmbient(Vector3f(0.2f, 0.2f, 0.2f));
        terrainMaterial->setDiffuse(Vector3f(0.5f, 0.5f, 0.5f));
        terrainMaterial->setSpecular(Vector3f(0.05f, 0.05f, 0.05f));
        terrainMaterial->setShininess(32.0f);

        terrainShader = new Shader;
        terrainShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/terrain.vert");
        terrainShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/terrain.frag");
        terrainShader->link();

        terrainShader->use();
        terrainShader->setInt("material.grass", 0);

        terrain = new Terrain;
        terrain->setShader(terrainShader);
        // terrain->generateFlatTerrain(512, 512);
        terrain->setMaterial(terrainMaterial);
        terrain->addTexture(diff);

        // Heightmap && noise settings
        HeightMap heightMap;
        heightMap.setScale(5);
        /*FPerlinNoise::OctaveSettings settings;
        settings.frequency = 0.0009f;
        settings.persistence = 0.3f;
        settings.octaves = 15;
        settings.amplitude = 10.0f;
        heightMap.perlinNoise(1024, 1024, 21412312, settings);*/
        //heightMap.diamondSquare(1025, 1025);
        heightMap.flat(512, 512);

        terrain->addHeightMap(&heightMap);
        // sceneManager()->sceneByKey("editor")->addToScene(terrain);

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

        // Lamp (object) shader
        lampShader = new Shader;
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lamp.vert");
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lamp.frag");
        lampShader->link();

        // Cube mesh
        Sphere sphere;
        mesh = new Mesh(sphere.vertices(), sphere.indices());

        // Add a new lamp (point light)
        lamp = new PointLight(mesh->vertices(), mesh->indices());
        lamp->setShader(lampShader);

        transform = new Transform;
        transform->setTranslation(200.0f, 5.0f, 135.0f);
        transform->scale(2.0f);

        lamp->setTransformation(transform);
        lamp->setId(0);
        lamp->setColor(Color(255.0f, 3.0f, 3.0f));
        lamp->setAttenuation(1.0f, 0.05f, 0.002f);
        sceneManager()->sceneByKey("editor")->addToScene("lamp", lamp);

        // Add a sun
        sun = new Sun;
        sun->setLightDirection(Vector3f(-0.2f, -1.0f, -1.3f));
        sceneManager()->sceneByKey("editor")->addToScene(sun);

        // TMP
        cubeShader = new Shader;
        cubeShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "../src/engine/shader/lighting.vert");
        cubeShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "../src/engine/shader/lighting.frag");
        cubeShader->link();

        Cube cube;
        cubeMesh = new Mesh(sphere.vertices(), sphere.indices());
        // cubeMesh = new Mesh("../resources/model/cube.obj");
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
        cubeTransform->setTranslation(210.0f, 3.0f, 140.0f);
        cubeTransform->setScale(3.0f);

        cubeModel = new Model;
        cubeModel->addMesh(cubeMesh);
        cubeModel->setTransformation(cubeTransform);
        cubeModel->setShader(cubeShader);
        sceneManager()->sceneByKey("editor")->addToScene("cube", cubeModel);
    }
}
