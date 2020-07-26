#include "iterrain.h"

namespace NAGE
{
    ITerrain::ITerrain()
        : mShader(new Shader),
          mMaterial(new Material),
          mTransform(new Transform)

    {

    }

    ITerrain::~ITerrain()
    {
        for(auto& texture : mTextures)
            delete texture.second;

        delete mShader;
        delete mMaterial;
        delete mTransform;
    }

    Shader* ITerrain::shader()
    {
        return mShader;
    }

    Material* ITerrain::material()
    {
        return mMaterial;
    }

    Transform* ITerrain::transform()
    {
        return mTransform;
    }

    unsigned int ITerrain::texturesCount() const
    {
        return mTextures.size();
    }

    Texture* ITerrain::textureByKey(const std::string& _key)
    {
        auto it = mTextures.find(_key);

        if(it == mTextures.end())
            return nullptr;

        return it->second;
    }

    std::map<std::string, Texture*> ITerrain::textures() const
    {
        return mTextures;
    }

    void ITerrain::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void ITerrain::setMaterial(Material* _material)
    {
        mMaterial = _material;
    }

    void ITerrain::setTransformation(Transform* _transform)
    {
        mTransform = _transform;
    }

    void ITerrain::addTexture(const std::string& _shaderUniformName, Texture* _texture)
    {
        if(!mShader)
            return;

        mShader->use();
        mShader->setInt(_shaderUniformName, mTextures.size());

        mTextures.insert(std::make_pair(_shaderUniformName, _texture));
    }

    void ITerrain::addTextures(const std::map<std::string, Texture*>&_textures)
    {
        mTextures = _textures;
    }

    void ITerrain::useMaterial()
    {
        if(mMaterial) mMaterial->use(mShader);
    }

    void ITerrain::bindTextures()
    {
        GLuint idx = 0;
        for(auto& texture : mTextures)
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
