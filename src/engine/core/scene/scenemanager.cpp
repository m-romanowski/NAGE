#include "scenemanager.h"

namespace mr::nage
{
    SceneManager::SceneManager()
    {

    }

    SceneManager::~SceneManager()
    {
        children_.clear();
    }

    SceneNode* SceneManager::sceneByKey(const std::string& _key)
    {
        std::unordered_map<std::string, SceneNode*>::const_iterator got = children_.find(_key);

        if(got != children_.end())
            return got->second;

        return nullptr;
    }

    std::unordered_map<std::string, SceneNode*> SceneManager::scenes() const
    {
        return children_;
    }

    SceneNode* SceneManager::createChild()
    {
        // Find a new key for scene node.
        std::string key;
        unsigned long size = children_.size();
        do
        {
            key = std::string("scene") + std::to_string(++size);
        } while(!Stl::checkKey(children_, key));

        // Append to scene manager container.
        SceneNode* sceneNode = new SceneNode(key);
        children_.insert(std::make_pair(key, sceneNode));
        Log::log(key + " (scene node) has been added to scene manager.");

        return sceneNode;
    }

    SceneNode* SceneManager::addChild(const std::string& _key)
    {
        if(Stl::checkKey(children_, _key))
        {
            std::error_code code = ERROR::SCENEMANAGER_FAILED_TO_ADD_NODE;
            Log::error(code.message());
            return nullptr;
        }

        auto sceneNode = new SceneNode(_key);
        children_.insert(std::make_pair(_key, sceneNode));
        Log::log(_key + " (scene node) has been added to scene manager.");

        return sceneNode;
    }

    void SceneManager::removeChild(const std::string& _key)
    {
        if(!Stl::checkKey(children_, _key))
        {
            // Print error if not find the key.
            std::error_code code = ERROR::SCENE_FAILED_TO_FIND_KEY;
            Log::error(code.message());
            return;
        }

        children_.erase(_key);
        Log::log(_key + " (scene node) has been removed from scene manager");
    }
}
