#include "scenenode.h"

namespace NAGE
{
    SceneNode::SceneNode()
        : mSkybox(nullptr),
          mSunLight(nullptr),
          mTerrain(nullptr),
          mCamera(new Camera)
    {

    }

    SceneNode::~SceneNode()
    {
        mModels.clear();
        mPointLights.clear();

        delete mCamera;

        if(mSkybox)
            delete mSkybox;

        if(mSunLight)
            delete mSunLight;
    }

    /* Add a new model object to the dictionary (models).
     */
    void SceneNode::addToScene(const std::string& _key, Model* _model)
    {
        // Check if the key already exists.
        if(STLUTIL::checkKey(mModels, _key) || STLUTIL::checkKey(mPointLights, _key))
        {
            std::error_code code = ERROR::SCENE_FAILED_TO_ADD_MODEL;
            Log::error(code.message());
            return;
        }

        // Add a new model to dictionary.
        mModels.insert(std::make_pair(_key, _model));
        Log::log(_key + " (model object) has been added.");
    }

    /* Add a new ligth to the dictionary (lights).
     */
    void SceneNode::addToScene(const std::string& _key, PointLight* _light)
    {
        // Check if the key already exists.
        if(STLUTIL::checkKey(mModels, _key) || STLUTIL::checkKey(mPointLights, _key))
        {
            std::error_code code = ERROR::SCENE_FAILED_TO_ADD_LIGHT;
            Log::error(code.message());
            return;
        }

        // Add a new ligth to dictionary.
        mPointLights.insert(std::make_pair(_key, _light));
        Log::log(_key + " (point light) has been added.");
    }

    void SceneNode::addToScene(Skybox* _skybox)
    {
        mSkybox = _skybox;
        Log::log("Skybox has been added.");
    }

    void SceneNode::addToScene(Sun* _light)
    {
        mSunLight = _light;
        Log::log("Sun light has been added.");
    }

    void SceneNode::addToScene(ITerrain* _terrain)
    {
        mTerrain = _terrain;
        Log::log("Terrain has been added.");
    }

    void SceneNode::addToScene(Camera* _camera)
    {
        mCamera = _camera;
        Log::log("Camera has been added.");
    }

    /* Remove object from the scene
     */
    void SceneNode::removeFromScene(const std::string _key)
    {
        // Check if key exists in any scene dictionaries (models, lights).
        if(STLUTIL::checkKey(mModels, _key))
        {
            mModels.erase(_key);
            Log::log(_key + " (model object) has been removed.");
            return;
        }

        if(STLUTIL::checkKey(mPointLights, _key))
        {
            mPointLights.erase(_key);
            Log::log(_key + " (point light) has been removed.");
            return;
        }

        // Print error if not find the key.
        std::error_code code = ERROR::SCENE_FAILED_TO_FIND_KEY;
        Log::error(code.message());
    }

    Model* SceneNode::getModelByKey(const std::string& _key)
    {
        std::unordered_map<std::string, Model*>::const_iterator got = mModels.find(_key);

        if(got != mModels.end())
            return got->second;

        return nullptr;
    }

    PointLight* SceneNode::getLightObjectByKey(const std::string& _key)
    {
        std::unordered_map<std::string, PointLight*>::const_iterator got = mPointLights.find(_key);

        if(got != mPointLights.end())
            return got->second;

        return nullptr;
    }

    Skybox* SceneNode::skybox()
    {
        return mSkybox;
    }

    Sun* SceneNode::sun()
    {
        return mSunLight;
    }

    ITerrain* SceneNode::terrain()
    {
        return mTerrain;
    }

    Camera* SceneNode::camera()
    {
        return mCamera;
    }

    void SceneNode::renderModels()
    {
        // Render models.
        for(const auto& model : mModels)
        {
            model.second->useMaterials();
            model.second->bindTextures();
            model.second->draw(mCamera);
        }
    }

    // TODO: change light rendering method.
    void SceneNode::renderLights()
    {
        // TMP: to change
        // Use light to any model on scene.
        for(auto& model : mModels)
        {
            for(auto& light : mPointLights)
                light.second->use(mCamera, model.second->shader());

            // Set point light count.
            model.second->shader()->setInt("pointLightCount", static_cast<int>(mPointLights.size()));

            // Set up sun light.
            if(mSunLight)
                mSunLight->use(mCamera, model.second->shader());
        }

        // TMP: to change
        if(mTerrain)
        {
            for(auto& light : mPointLights)
                light.second->use(mCamera, mTerrain->shader());

            mTerrain->shader()->setInt("pointLightCount", static_cast<int>(mPointLights.size()));

            if(mSunLight)
                mSunLight->use(mCamera, mTerrain->shader());
        }

        // Draw lights
        for(const auto& light : mPointLights)
            light.second->draw(mCamera);

        if(mSunLight)
            mSunLight->draw(mCamera);
    }

    void SceneNode::renderSkybox()
    {
        // Render skybox if exists
        if(mSkybox)
            mSkybox->draw(*mCamera);
    }

    void SceneNode::renderTerrain()
    {
        if(mTerrain)
        {
            mTerrain->useMaterial();
            mTerrain->bindTextures();
            mTerrain->render(mCamera);
        }
    }
}
