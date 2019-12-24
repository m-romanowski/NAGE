#include "scenemanager.h"

namespace NAGE
{
    SceneManager::SceneManager()
    {

    }

    SceneManager::~SceneManager()
    {
        mChildren.clear();
    }

    SceneNode* SceneManager::sceneByKey(const std::string& _key)
    {
        std::unordered_map<std::string, SceneNode*>::const_iterator got = mChildren.find(_key);

        if(got != mChildren.end())
            return got->second;

        return nullptr;
    }

    std::unordered_map<std::string, SceneNode*> SceneManager::scenes() const
    {
        return mChildren;
    }

    SceneNode* SceneManager::createChild()
    {
        // Find a new key for scene node.
        std::string key;
        unsigned long size = mChildren.size();
        do
        {
            key = std::string("scene") + std::to_string(++size);

        } while(!STL_UTIL::checkKey(mChildren, key));

        // Append to scene manager container.
        SceneNode* sceneNode = new SceneNode;
        mChildren.insert(std::make_pair(key, sceneNode));
        Log::log(key + " (scene node) has been added to scene manager.");

        return sceneNode;
    }

    void SceneManager::addChild(const std::string& _key, SceneNode* _node)
    {
        if(STL_UTIL::checkKey(mChildren, _key))
        {
            std::error_code code = ERROR::SCENEMANAGER_FAILED_TO_ADD_NODE;
            Log::error(code.message());
            return;
        }

        mChildren.insert(std::make_pair(_key, _node));
        Log::log(_key + " (scene node) has been added to scene manager.");
    }

    void SceneManager::removeChild(const std::string& _key)
    {
        if(!STL_UTIL::checkKey(mChildren, _key))
        {
            // Print error if not find the key.
            std::error_code code = ERROR::SCENE_FAILED_TO_FIND_KEY;
            Log::error(code.message());
            return;
        }

        mChildren.erase(_key);
        Log::log(_key + " (scene node) has been removed from scene manager");
    }
}
