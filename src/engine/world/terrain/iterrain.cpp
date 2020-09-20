#include "iterrain.h"

namespace NAGE
{
    ITerrain::ITerrain()
        : shader_(new Shader),
          material_(new Material),
          transform_(new Transform)

    {

    }

    ITerrain::~ITerrain()
    {
        for(auto& texture : textures_)
            delete texture.second;

        delete shader_;
        delete material_;
        delete transform_;
    }

    Shader* ITerrain::shader()
    {
        return shader_;
    }

    Material* ITerrain::material()
    {
        return material_;
    }

    Transform* ITerrain::transform()
    {
        return transform_;
    }

    unsigned int ITerrain::texturesCount() const
    {
        return textures_.size();
    }

    Texture* ITerrain::textureByKey(const std::string& _key)
    {
        auto it = textures_.find(_key);

        if(it == textures_.end())
            return nullptr;

        return it->second;
    }

    std::map<std::string, Texture*> ITerrain::textures() const
    {
        return textures_;
    }

    void ITerrain::setShader(Shader* _shader)
    {
        shader_ = _shader;
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
        if(!shader_)
            return;

        shader_->use();
        shader_->setInt(_shaderUniformName, textures_.size());

        textures_.insert(std::make_pair(_shaderUniformName, _texture));
    }

    void ITerrain::addTextures(const std::map<std::string, Texture*>&_textures)
    {
        textures_ = _textures;
    }

    void ITerrain::useMaterial()
    {
        if(material_) material_->use(shader_);
    }

    void ITerrain::bindTextures()
    {
        GLuint idx = 0;
        for(auto& texture : textures_)
        {
            if(texture.second)
            {
                glActiveTexture(GL_TEXTURE0 + idx);
                glBindTexture(GL_TEXTURE_2D, texture.second->id());
                idx++;
            }
        }
    }

    void ITerrain::unbindTextures()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
