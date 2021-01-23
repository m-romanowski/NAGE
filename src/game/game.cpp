#include "game.h"

namespace mr::nage
{
    Game::Game(FpsLimit _limit)
        : IGame(_limit),
          currHour(20),
          currMin(0)
    {

    }

    void Game::initializeScene()
    {
        sceneManager()->addChild("world");
        sceneManager()->sceneByKey("world")->camera()->translate(80.0f, 250.0f, 250.0f);

        // Skybox
        skyboxShader = std::make_shared<Shader>();
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
             "src/engine/shader/dayNight.vert");
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "src/engine/shader/dayNight.frag");
        skyboxShader->link();

        skybox = std::make_shared<DayNightSkybox>("Day-night skybox", skyboxShader.get());
        sceneManager()->sceneByKey("world")->addToScene(skybox.get());

        // Skybox
        /*
        skyboxShader = std::make_shared<Shader>();
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
             "src/engine/shader/dayNight.vert");
        skyboxShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "src/engine/shader/dayNight.frag");
        skyboxShader->link();

        std::vector<std::string> skyboxFaces = {
            "resources/texture/skybox/2/right.jpg",
            "resources/texture/skybox/2/left.jpg",
            "resources/texture/skybox/2/top.jpg",
            "resources/texture/skybox/2/bottom.jpg",
            "resources/texture/skybox/2/front.jpg",
            "resources/texture/skybox/2/back.jpg",
        };

        skybox = std::make_shared<Skybox>("Skybox", skyboxShader.get());
        skybox->addFacesTextures(skyboxFaces);
        sceneManager()->sceneByKey("world")->addToScene(skybox.get());
        */

        // Lamp
        // Sphere sphere("Red lamp");

        // lampTransform = std::make_shared<Transform>();
        // lampTransform->setTranslation(430.0f, 80.0f, 455.0f);
        // lampTransform->scale(2.0f);

        lampShader = std::make_shared<Shader>();
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_VERTEX,
            "src/engine/shader/lamp.vert");
        lampShader->addShaderFromSourceFile(SHADER_TYPE::SHADER_FRAGMENT,
            "src/engine/shader/lamp.frag");
        lampShader->link();
        // lampShader->use();
        // lampShader->setFloat("expand", 0.25f);
        // lampShader->setVec2("center", lampTransform->translation().x(), lampTransform->translation().y());
        // lampShader->setFloat("radius", sphere.radius());
        // lampShader->setFloat("windowHeight", IWindow::currentWindowSize().y());

        // Mesh mesh("Sun mesh", sphere.vertices(), sphere.indices(), nullptr);
        // lamp = std::make_shared<PointLightObject>(sphere.id(), mesh.vertices(), mesh.indices());
        // lamp->setShader(lampShader.get());

        // lamp->setTransformation(lampTransform.get());
        // lamp->setId(0);
        // lamp->setColor(Color(255.0f, 0.0f, 0.0f));
        // lamp->setAttenuation(1.0f, 0.05f, 0.002f);

        // sceneManager()->sceneByKey("world")->addToScene(lamp.get());

        // Sun
        sun = std::make_shared<SunLight>();
        sun->setShader(lampShader.get());
        sun->setColor(Color(238, 220, 165));
        sun->setGradientExpand(0.25f);
        sun->setLightDirection(Vector3f(-0.2f, -1.0f, -1.3f));
        sun->transformation()->setScale(20.0f);
        sun->transformation()->setTranslation(430.0f, 1000.0f, 455.0f);
        sceneManager()->sceneByKey("world")->addToScene(sun.get());

        // CDLOD water
        waterHeightmap = std::make_shared<HeightMap>();
        waterHeightmap->flat(4096, 4096);

        Transform* waterTransform = new Transform;
        waterTransform->setTranslation(0.0f, 200.0f, 0.0f);

        CDLODSettings waterLodSettings;
        waterLodSettings.gridResolution_ = 16;

        cdlodWater = std::make_shared<CDLODWater>("CDLOD water", 11, waterHeightmap.get(), waterLodSettings);
        cdlodWater->setWaveNoiseFactor(120.0f);
        // cdlodWater->setupFlowMapEffect(256, 256);
        cdlodWater->setWaveFrequency(0.1f);
        cdlodWater->setHeightMapProperties(cdlodWater->shader());
        cdlodWater->setTransformation(waterTransform);
        sceneManager()->sceneByKey("world")->addToScene(cdlodWater.get());

        // CDLOD terrain
//        CDLODSettings terrainLodSettings;
//        terrainLodSettings.maxLODLevel_ = 128;
//        terrainLodSettings.leafNodeSize_ = 1;
//        terrainLodSettings.gridResolution_ = 128;
//        terrainLodSettings.gridMeshesCount_ = 9;

//        heightMap = std::make_shared<HeightMap>();
//        heightMap->loadFromFile("resources/texture/terrain/heightmap1_2k.jpg");

//        blendmap = std::make_shared<Texture>("resources/texture/terrain/blendmap1_2k.jpg", TextureType::TEXTURE_2D);
//        terrainTexture1 = std::make_shared<Texture>("resources/texture/terrain/dirt.jpg", TextureType::TEXTURE_2D);
//        terrainTexture2 = std::make_shared<Texture>("resources/texture/terrain/grass.jpg", TextureType::TEXTURE_2D);
//        terrainTexture3 = std::make_shared<Texture>("resources/texture/terrain/stone.jpg", TextureType::TEXTURE_2D);
//        terrainTexture4 = std::make_shared<Texture>("resources/texture/terrain/snow.jpg", TextureType::TEXTURE_2D);

//        cdlodTerrain = std::make_shared<CDLODTerrain>("CDLOD terrain", 11, heightMap.get(), terrainLodSettings);

//        cdlodTerrain->addTexture("material.blendmap", blendmap.get());
//        cdlodTerrain->addTexture("material.dirt", terrainTexture1.get());
//        cdlodTerrain->addTexture("material.grass", terrainTexture2.get());
//        cdlodTerrain->addTexture("material.stone", terrainTexture3.get());
//        cdlodTerrain->addTexture("material.snow", terrainTexture4.get());
//        cdlodTerrain->setHeightMapProperties(cdlodTerrain->shader());

//        sceneManager()->sceneByKey("world")->addToScene(cdlodTerrain.get());

        // Geoclipmapping terrain
        heightMap = std::make_shared<HeightMap>();
        heightMap->loadFromFile("resources/texture/terrain/heightmap1_2k.jpg");

        blendmap = std::make_shared<Texture>("resources/texture/terrain/blendmap1_2k.jpg", TextureType::TEXTURE_2D);
        terrainTexture1 = std::make_shared<Texture>("resources/texture/terrain/dirt.jpg", TextureType::TEXTURE_2D);
        terrainTexture2 = std::make_shared<Texture>("resources/texture/terrain/grass.jpg", TextureType::TEXTURE_2D);
        terrainTexture3 = std::make_shared<Texture>("resources/texture/terrain/stone.jpg", TextureType::TEXTURE_2D);
        terrainTexture4 = std::make_shared<Texture>("resources/texture/terrain/snow.jpg", TextureType::TEXTURE_2D);

        geoclipmapTerrain = std::make_shared<GeoClipMapTerrain>("Geoclipmap terrain", heightMap.get(), 500.0f, 10);

        geoclipmapTerrain->addTexture("material.blendmap", blendmap.get());
        geoclipmapTerrain->addTexture("material.dirt", terrainTexture1.get());
        geoclipmapTerrain->addTexture("material.grass", terrainTexture2.get());
        geoclipmapTerrain->addTexture("material.stone", terrainTexture3.get());
        geoclipmapTerrain->addTexture("material.snow", terrainTexture4.get());

        sceneManager()->sceneByKey("world")->addToScene(geoclipmapTerrain.get());
    }

    void Game::ioEventsSupplier()
    {
        if(nage::Mouse::mouseButtonPressed(nage::MouseButton::X11_RIGHT_BUTTON))
        {
            Camera* camera = sceneManager()->sceneByKey("world")->camera();

            // Handle camera rotations.
            camera->rotate(-nage::cameraSensitivity * nage::Mouse::mouseDelta().x(),
                nage::Vector3f::up);

            // TODO: fix water effect.
//            camera->rotate(-nage::cameraSensitivity * nage::Mouse::mouseDelta().y(),
//                camera->right());

            // Handle camera translations.
            nage::Vector3f translation;
            if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_W)) translation -= camera->forward();
            if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_S)) translation += camera->forward();
            if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_A)) translation -= camera->right();
            if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_D)) translation += camera->right();
            if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_Q)) translation -= camera->up();
            if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_E)) translation += camera->up();

            float delta = static_cast<float>(IWindow::deltaMs());
            camera->translate(nage::cameraMovementSpeed * delta * translation);
        }

        if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_O))
        {
            currMin++;
            if(currMin > 59)
            {
                currHour++;
                currMin = 0;
            }

            if(currHour >= 24)
                currHour = 0;

            printWorldHourLog();
        }

        if(nage::Keyboard::keyPressed(nage::Key::X11_KEY_P))
        {
            currMin--;
            if(currMin < 0)
            {
                currHour--;
                currMin = 59;
            }

            if(currHour < 0)
                currHour = 23;

            printWorldHourLog();
        }

        skybox->setTimeSupplier([this]() -> DayNightSkybox::Time {
            return DayNightSkybox::Time(currHour, currMin, 0);
        });
    }

    std::string Game::addTrailingZeroIfNeeded(int _x)
    {
        if(_x < 10)
            return "0" + std::to_string(_x);

        return std::to_string(_x);
    }

    void Game::printWorldHourLog()
    {
        Log::log("Current world hour: " + addTrailingZeroIfNeeded(currHour) + ":" + addTrailingZeroIfNeeded(currMin));
    }
}
