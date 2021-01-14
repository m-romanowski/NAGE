#ifndef NAGE_ENGINE_CORE_SCENE_SCENENODE_H_
#define NAGE_ENGINE_CORE_SCENE_SCENENODE_H_

#include "common/log.h"
#include "engine/util/stl.h"
#include "engine/render/renderableobject.h"
#include "engine/components/camera/camera.h"

#include <string>
#include <unordered_map>
#include <optional>
#include <algorithm>

namespace mr::nage
{
    class SceneNode
    {
        struct ObjectIdentity
        {
            std::string name_;

            friend bool operator==(const ObjectIdentity& _lhs, const ObjectIdentity& _rhs)
            {
                return _lhs.name_ == _rhs.name_;
            }

            friend bool operator!=(const ObjectIdentity& _lhs, const ObjectIdentity& _rhs)
            {
                return !(_lhs == _rhs);
            }


            ObjectIdentity(const std::string& _name)
            {
                this->name_ = _name;
            }

            static ObjectIdentity of(const std::string& _name)
            {
                return ObjectIdentity(_name);
            }
        };

        struct ObjectIdentityHasher
        {
            size_t operator()(ObjectIdentity const& key) const
            {
                return ((std::hash<std::string>()(key.name_) << 1)) >> 1;
            }
        };

    public:
        explicit SceneNode(const std::string _name);
        ~SceneNode();

        std::string name() const;
        std::optional<RenderableObject*> renderableObjectByName(const std::string& _name) const;
        std::vector<RenderableObject*> renderableObjects() const;
        Camera* camera() const;

        void addToScene(RenderableObject* _object);
        void removeFromScene(const std::string& _name);

    private:
        std::vector<RenderableObject*> objectsByType(const std::string _expectedType) const;
        std::optional<ObjectIdentity> objectIdentityByName(const std::string& _name) const;
        std::optional<std::pair<ObjectIdentity, RenderableObject*>> findComponentByName(const std::string& _name) const;

        std::string name_;
        std::unordered_map<ObjectIdentity, RenderableObject*, ObjectIdentityHasher> sceneComponents_;
        Camera* camera_;
    };
}


#endif // NAGE_ENGINE_CORE_SCENE_SCENENODE_H_
