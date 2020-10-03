#ifndef NAGE_ENGINE_CORE_SCENE_SCENEMANAGER_H_
#define NAGE_ENGINE_CORE_SCENE_SCENEMANAGER_H_

#include "scenenode.h"
#include "engine/util/stl.h"

#include <unordered_map>

namespace mr::nage
{
    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

        SceneNode* sceneByKey(const std::string& _key);
        std::unordered_map<std::string, SceneNode*> scenes() const;

        // Child operations.
        SceneNode* createChild();
        void addChild(const std::string& _key, SceneNode* _node);
        void removeChild(const std::string& _key);

    private:
        std::unordered_map<std::string, SceneNode*> children_;
    };
}

#endif // NAGE_ENGINE_CORE_SCENE_SCENEMANAGER_H_
