#include "scenenode.h"

namespace NAGE
{
    SceneNode::SceneNode()
        : skybox_(nullptr),
          sunLight_(nullptr),
          terrain_(nullptr),
          water_(nullptr),
          camera_(new Camera)
    {

    }

    SceneNode::~SceneNode()
    {
        models_.clear();
        pointLights_.clear();

        delete camera_;
        delete skybox_;
        delete sunLight_;
        delete terrain_;
        delete water_;
    }

    /* Add a new model object to the dictionary (models).
     */
    void SceneNode::addToScene(const std::string& _key, Model* _model)
    {
        // Check if the key already exists.
        if(STLUTIL::checkKey(models_, _key) || STLUTIL::checkKey(pointLights_, _key))
        {
            std::error_code code = ERROR::SCENE_FAILED_TO_ADD_MODEL;
            Log::error(code.message());
            return;
        }

        // Add a new model to dictionary.
        models_.insert(std::make_pair(_key, _model));
        Log::log(_key + " (model object) has been added.");
    }

    /* Add a new ligth to the dictionary (lights).
     */
    void SceneNode::addToScene(const std::string& _key, PointLight* _light)
    {
        // Check if the key already exists.
        if(STLUTIL::checkKey(models_, _key) || STLUTIL::checkKey(pointLights_, _key))
        {
            std::error_code code = ERROR::SCENE_FAILED_TO_ADD_LIGHT;
            Log::error(code.message());
            return;
        }

        // Add a new ligth to dictionary.
        pointLights_.insert(std::make_pair(_key, _light));
        Log::log(_key + " (point light) has been added.");
    }

    void SceneNode::addToScene(Skybox* _skybox)
    {
        skybox_ = _skybox;
        Log::log("Skybox has been added.");
    }

    void SceneNode::addToScene(Sun* _light)
    {
        sunLight_ = _light;
        Log::log("Sun light has been added.");
    }

    void SceneNode::addToScene(ITerrain* _terrain)
    {
        terrain_ = _terrain;
        Log::log("Terrain has been added.");
    }

    void SceneNode::addToScene(IWater* _water)
    {
        water_ = _water;
        Log::log("Water has been added.");
    }

    void SceneNode::addToScene(Camera* _camera)
    {
        camera_ = _camera;
        Log::log("Camera has been added.");
    }

    /* Remove object from the scene
     */
    void SceneNode::removeFromScene(const std::string _key)
    {
        // Check if key exists in any scene dictionaries (models, lights).
        if(STLUTIL::checkKey(models_, _key))
        {
            models_.erase(_key);
            Log::log(_key + " (model object) has been removed.");
            return;
        }

        if(STLUTIL::checkKey(pointLights_, _key))
        {
            pointLights_.erase(_key);
            Log::log(_key + " (point light) has been removed.");
            return;
        }

        // Print error if not find the key.
        std::error_code code = ERROR::SCENE_FAILED_TO_FIND_KEY;
        Log::error(code.message());
    }

    Model* SceneNode::getModelByKey(const std::string& _key)
    {
        std::unordered_map<std::string, Model*>::const_iterator got = models_.find(_key);

        if(got != models_.end())
            return got->second;

        return nullptr;
    }

    PointLight* SceneNode::getLightObjectByKey(const std::string& _key)
    {
        std::unordered_map<std::string, PointLight*>::const_iterator got = pointLights_.find(_key);

        if(got != pointLights_.end())
            return got->second;

        return nullptr;
    }

    Skybox* SceneNode::skybox()
    {
        return skybox_;
    }

    Sun* SceneNode::sun()
    {
        return sunLight_;
    }

    ITerrain* SceneNode::terrain()
    {
        return terrain_;
    }

    IWater* SceneNode::water()
    {
        return water_;
    }

    Camera* SceneNode::camera()
    {
        return camera_;
    }

    void SceneNode::renderModels(Vector4f _clipPlane)
    {
        // Render models.
        for(const auto& model : models_)
        {
            model.second->useMaterials();
            model.second->bindTextures();
            model.second->draw(camera_, _clipPlane);
            // model.second->unbindTextures();
        }
    }

    // TODO: change light rendering method.
    void SceneNode::renderLights()
    {
        // Use light to any model on scene.
        for(auto& model : models_)
        {
            for(auto& light : pointLights_)
                light.second->use(camera_, model.second->shader());

            // Set point light count.
            model.second->shader()->setInt("pointLightCount", static_cast<int>(pointLights_.size()));

            // Set up sun light.
            if(sunLight_)
                sunLight_->use(camera_, model.second->shader());
        }

        if(terrain_)
        {
            for(auto& light : pointLights_)
                light.second->use(camera_, terrain_->shader());

            terrain_->shader()->setInt("pointLightCount", static_cast<int>(pointLights_.size()));

            if(sunLight_)
                sunLight_->use(camera_, terrain_->shader());
        }

        // Draw lights
        for(const auto& light : pointLights_)
            light.second->draw(camera_);

        if(sunLight_)
            sunLight_->draw(camera_);
    }

    void SceneNode::renderSkybox()
    {
        // Render skybox if exists
        if(skybox_)
            skybox_->draw(camera_);
    }

    void SceneNode::renderTerrain(Vector4f _clipPlane)
    {
        if(terrain_)
        {
            terrain_->useMaterial();
            terrain_->bindTextures();
            terrain_->render(camera_, _clipPlane);
            // mTerrain->unbindTextures();
        }
    }

    void SceneNode::renderWater()
    {
        if(water_)
        {
            water_->bindTextures();
            water_->render(camera_);
            // mWater->unbindTextures();
        }
    }

    void SceneNode::renderAllComponents(Vector4f _clipPlane)
    {
        renderSkybox();
        renderModels(_clipPlane);
        renderLights();
        renderTerrain(_clipPlane);
        renderWater();
    }
}
