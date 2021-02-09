#include "iterrain.h"

#include <QDebug>

namespace mr::nage
{
    ITerrain::ITerrain(const std::string& _id)
        : id_(_id),
          resource_(new Resource(_id)),
          material_(new Material),
          transform_(new Transform)

    {
        this->resource_->setShader(new Shader);
    }

    ITerrain::~ITerrain()
    {
        delete material_;
        delete transform_;
        delete resource_;
    }

    std::string ITerrain::id() const
    {
        return id_;
    }

    Shader* ITerrain::shader()
    {
        return resource_->shader();
    }

    Material* ITerrain::material()
    {
        return material_;
    }

    Transform* ITerrain::transformation()
    {
        return transform_;
    }

    Resource* ITerrain::resource()
    {
        return this->resource_;
    }

    // unsigned int ITerrain::texturesCount() const
    // {
    //     return textures_.size();
    // }

    // Texture* ITerrain::textureByKey(const std::string& _key)
    // {
    //     auto it = textures_.find(_key);

    //     if(it == textures_.end())
    //         return nullptr;

    //     return it->second;
    // }

    // std::map<std::string, Texture*> ITerrain::textures() const
    // {
    //     return textures_;
    // }

    void ITerrain::setShader(Shader* _shader)
    {
        this->resource_->setShader(_shader);
    }

    void ITerrain::setMaterial(Material* _material)
    {
        material_ = _material;
    }

    void ITerrain::setTransformation(Transform* _transform)
    {
        transform_ = _transform;
    }

    void ITerrain::addTexture(const std::string& _shaderUniformName, Texture* _texture)
    {
        this->resource_->mapTexture(_shaderUniformName, _texture);
    }

    // void ITerrain::addTextures(const std::map<std::string, Texture*>&_textures)
    // {
    //     textures_ = _textures;
    // }

    void ITerrain::useMaterials()
    {
        if(material_)
            material_->use(this->resource_->shader());
    }

    void ITerrain::bindTextures()
    {
        GLuint idx = 0;
        for(auto& texture : this->resource_->textures())
        {
            if(texture)
            {
                glActiveTexture(GL_TEXTURE0 + idx);
                glBindTexture(GL_TEXTURE_2D, texture->id());
                idx++;
            }
        }
    }

    void ITerrain::unbindTextures()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
