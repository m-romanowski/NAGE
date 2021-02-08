#include "resource.h"

namespace mr::nage
{
    Resource::Resource(const std::string _sourceId)
        : sourceId_(_sourceId),
          shader_(nullptr)
    {

    }

    Resource::shader_ptr_t Resource::shader() const
    {
        return shader_;
    }

    std::vector<Resource::texture_ptr_t> Resource::textures() const
    {
        std::vector<texture_ptr_t> result;
        for(auto texture : textures_)
            result.push_back(texture.second);

        return result;
    }

    void Resource::setShader(shader_ptr_t _shader)
    {
        if(shader_)
            return;

        this->shader_ = _shader;
    }

    void Resource::mapTexture(const std::string _materialName, texture_ptr_t _texture)
    {
        auto item = textures_.find(_materialName);
        if(item == textures_.end() && shader_)
        {
            shader_->use();
            shader_->setInt(_materialName, textures_.size());

            textures_.insert({_materialName, _texture});
        }
    }
}
