#include "scenenode.h"

namespace mr::nage
{
    SceneNode::SceneNode(const std::string _name)
        : name_(_name),
          camera_(new Camera)
    {

    }

    SceneNode::~SceneNode()
    {
        for(auto& component : sceneComponents_)
            delete component.second;

        sceneComponents_.clear();

        delete camera_;
    }

    std::string SceneNode::name() const
    {
        return name_;
    }

    std::optional<RenderableObject*> SceneNode::renderableObjectByName(const std::string& _name) const
    {
        if(auto it = findComponentByName(_name); it)
        {
            if(it.has_value())
                return std::optional<RenderableObject*>{ it->second };
        }

        return std::nullopt;
    }

    std::vector<RenderableObject*> SceneNode::renderableObjects() const
    {
        return objectsByType(RenderableObject::TYPE);
    }

    Camera* SceneNode::camera() const
    {
        return camera_;
    }

    void SceneNode::addToScene(RenderableObject* _object)
    {
        auto objectId = _object->id();
        if(objectId.empty())
            throw std::runtime_error("Cannot add new object with empty identifier");

        // Check if the key already exists.
        if(auto it = findComponentByName(objectId); it.has_value())
        {
            std::error_code code = ERROR::SCENE_FAILED_TO_ADD_OBJECT;
            Log::error(code.message());
            return;
        }

        // Add a new ligth to dictionary.
        sceneComponents_.insert(std::make_pair(SceneNode::ObjectIdentity::of(objectId), _object));
        Log::debug(objectId + " has been added to the scene.");
    }

    void SceneNode::removeFromScene(const std::string& _name)
    {
        // Check if key exists in any scene dictionaries (models, lights).
        if(auto identity = objectIdentityByName(_name); identity)
        {
            sceneComponents_.erase(identity.value());
            Log::debug(_name + " has been removed from the scene node.");
            return;
        }

        // Print error if not find the key.
        std::error_code code = ERROR::SCENE_FAILED_TO_FIND_KEY;
        Log::error(code.message());
    }

    std::vector<RenderableObject*> SceneNode::objectsByType(const std::string _expectedType) const
    {
        std::vector<RenderableObject*> result;
        for(auto& component : sceneComponents_)
        {
            if(component.second->type() == _expectedType)
                result.push_back(component.second);
        }

        return result;
    }

    std::optional<SceneNode::ObjectIdentity> SceneNode::objectIdentityByName(const std::string &_name) const
    {
        if(auto it = findComponentByName(_name); it.has_value())
            return std::optional<SceneNode::ObjectIdentity>{ it->first };

        return std::nullopt;
    }

    std::optional<std::pair<SceneNode::ObjectIdentity, RenderableObject*>> SceneNode::findComponentByName(const std::string& _name) const
    {
        using pair = std::pair<ObjectIdentity, RenderableObject*>;

        auto it = std::find_if(sceneComponents_.begin(), sceneComponents_.end(), [&](const pair& _identity) {
            return _identity.first.name_ == _name;
        });

        if(it != sceneComponents_.end())
            return std::optional<pair>{ *it };

        return std::nullopt;
    }
}
