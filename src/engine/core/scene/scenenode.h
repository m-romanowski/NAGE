#ifndef NAGE_ENGINE_CORE_SCENE_SCENENODE_H_
#define NAGE_ENGINE_CORE_SCENE_SCENENODE_H_

#include "common/log.h"
#include "engine/util/stl.h"
#include "engine/components/camera/camera.h"
#include "engine/render/model/model.h"
#include "engine/world/light/pointlight.h"
#include "engine/world/light/sun.h"
#include "engine/world/skybox/skybox.h"
#include "engine/world/terrain/iterrain.h"

#include <string>
#include <unordered_map>

namespace NAGE
{
    class SceneNode
    {
    public:
        SceneNode();
        ~SceneNode();

        // Getters
        Model* getModelByKey(const std::string& _key);
        PointLight* getLightObjectByKey(const std::string& _key);
        Camera* camera();
        Skybox* skybox();
        Sun* sun();
        ITerrain* terrain();

        // Childs oprations.
        void addToScene(const std::string& _key, Model* _model); // Models
        void addToScene(const std::string& _key, PointLight* _light); // Lights
        void addToScene(Skybox* _skybox); // Skybox
        void addToScene(Sun* _sunLight); // Sun light
        void addToScene(ITerrain* _terrain); // Terrain
        void addToScene(Camera* _camera); // Scene camera
        void removeFromScene(const std::string _key);
        void renderModels();
        void renderLights();
        void renderSkybox();
        void renderTerrain();

    private:
        std::unordered_map<std::string, Model*> mModels;
        std::unordered_map<std::string, PointLight*> mPointLights;
        Skybox* mSkybox;
        Sun* mSunLight;
        ITerrain* mTerrain;
        Camera* mCamera;
    };
}

#endif // NAGE_ENGINE_CORE_SCENE_SCENENODE_H_
