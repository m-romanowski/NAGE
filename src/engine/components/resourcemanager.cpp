#include "resourcemanager.h"

namespace mr::nage
{
    ResourceManager::~ResourceManager()
    {
        textures_.clear();
    }

    std::size_t ResourceManager::addTexture(texture_ptr _texture)
    {
        textures_.insert(std::make_pair(textures_.size() + 1, _texture));
        return textures_.size();
    }

    GLuint ResourceManager::getTexture(const std::size_t _id)
    {
        auto it = textures_.find(_id);
        if(it != textures_.end())
            return it->second->id();

        throw std::invalid_argument("Cannot find texture");
    }

    void ResourceManager::removeTexture(const std::uint64_t _id)
    {
        auto it = textures_.find(_id);
        if(it != textures_.end())
            textures_.erase(it);
    }

    std::size_t ResourceManager::addModel(model_ptr _model)
    {
        models_.insert(std::make_pair(models_.size() + 1, _model));
        return models_.size();
    }

    ResourceManager::model_ptr ResourceManager::getModel(const std::size_t _id)
    {
        auto it = models_.find(_id);
        if(it != models_.end())
            return it->second;

        throw std::invalid_argument("Cannot find model");
    }

    void ResourceManager::removeModel(const std::size_t _id)
    {
        auto it = models_.find(_id);
        if(it != models_.end())
            models_.erase(it);
    }
}
