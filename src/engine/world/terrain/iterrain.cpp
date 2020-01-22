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

    std::vector<Texture*> ITerrain::textures() const
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

    void ITerrain::addTexture(Texture* _texture)
    {
        mTextures.push_back(_texture);
    }

    void ITerrain::addTextures(const std::vector<Texture*>&_textures)
    {
        mTextures = _textures;
    }

    void ITerrain::useMaterial()
    {
        if(mMaterial) mMaterial->use(mShader);
    }

    void ITerrain::bindTextures()
    {
        for(GLuint i = 0; i < mTextures.size(); i++)
        {
            if(mTextures[i])
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, mTextures[i]->id());
            }
        }
    }
}
