#include "iwater.h"

namespace NAGE
{
    IWater::IWater()
        : mShader(new Shader),
          mMaterial(new Material),
          mTransform(new Transform)

    {

    }

    IWater::~IWater()
    {
        for(auto& texture : mTextures)
            delete texture.second;

        delete mShader;
        delete mMaterial;
        delete mTransform;
    }

    Shader* IWater::shader()
    {
        return mShader;
    }

    Material* IWater::material()
    {
        return mMaterial;
    }

    Transform* IWater::transform()
    {
        return mTransform;
    }

    unsigned int IWater::texturesCount() const
    {
        return mTextures.size();
    }

    Texture* IWater::textureByKey(const std::string& _key)
    {
        auto it = mTextures.find(_key);

        if(it == mTextures.end())
            return nullptr;

        return it->second;
    }

    std::map<std::string, Texture*> IWater::textures() const
    {
        return mTextures;
    }

    void IWater::setShader(Shader* _shader)
    {
        mShader = _shader;
    }

    void IWater::setMaterial(Material* _material)
    {
        mMaterial = _material;
    }

    void IWater::setTransformation(Transform* _transform)
    {
        mTransform = _transform;
    }

    void IWater::addTexture(const std::string& _shaderUniformName, Texture* _texture)
    {
        if(!mShader)
            return;

        mShader->use();
        mShader->setInt(_shaderUniformName, mTextures.size());

        mTextures.insert(std::make_pair(_shaderUniformName, _texture));
    }

    void IWater::addTextures(const std::map<std::string, Texture*>&_textures)
    {
        mTextures = _textures;
    }

    void IWater::useMaterial()
    {
        if(mMaterial) mMaterial->use(mShader);
    }

    void IWater::bindTextures()
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
}
