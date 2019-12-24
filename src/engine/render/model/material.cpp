#include "material.h"

namespace NAGE
{
    Material::Material()
        : texturesSent(false)
    {

    }

    Material::Material(const Material& _rhs)
        : texturesSent(false)
    {
        mAmbient = _rhs.mAmbient;
        mDiffuse = _rhs.mDiffuse;
        mSpecular = _rhs.mSpecular;
        mShininess = _rhs.mShininess;
        mDiffuseTexture = _rhs.mDiffuseTexture;
        mSpecularTexture = _rhs.mSpecularTexture;
    }

    Material::Material(const Vector3f& _ambient, const Vector3f& _diffuse, const Vector3f& _specular,
        const GLfloat _shininess)
        : mAmbient(_ambient),
          mDiffuse(_diffuse),
          mSpecular(_specular),
          mShininess(_shininess),
          texturesSent(false)
    {

    }

    Material::Material(const Vector3f& _ambient, const Vector3f& _diffuse, const Vector3f& _specular,
        const GLfloat _shininess, const GLuint _diffuseTexture, const GLuint _specularTexture)
        : mAmbient(_ambient),
          mDiffuse(_diffuse),
          mSpecular(_specular),
          mShininess(_shininess),
          mDiffuseTexture(_diffuseTexture),
          mSpecularTexture(_specularTexture),
          texturesSent(false)
    {

    }

    Vector3f Material::ambient() const
    {
        return mAmbient;
    }

    Vector3f Material::diffuse() const
    {
        return mDiffuse;
    }

    Vector3f Material::specular() const
    {
        return mSpecular;
    }

    float Material::shininess() const
    {
        return mShininess;
    }

    GLuint Material::diffuseTexture() const
    {
        return mDiffuseTexture;
    }

    GLuint Material::specularTexture() const
    {
        return mSpecularTexture;
    }

    void Material::setAmbient(const Vector3f& _ambient)
    {
        mAmbient = _ambient;
    }

    void Material::setAmbient(float _x, float _y, float _z)
    {
        mAmbient = Vector3f(_x, _y, _z);
    }

    void Material::setDiffuse(const Vector3f& _diffuse)
    {
        mDiffuse = _diffuse;
    }

    void Material::setDiffuse(float _x, float _y, float _z)
    {
        mDiffuse = Vector3f(_x, _y, _z);
    }

    void Material::setSpecular(const Vector3f& _specular)
    {
        mSpecular = _specular;
    }

    void Material::setSpecular(float _x, float _y, float _z)
    {
        mSpecular = Vector3f(_x, _y, _z);
    }

    void Material::setShininess(const GLfloat _shinines)
    {
        mShininess = _shinines;
    }

    void Material::setDiffuseTexture(const GLuint _textureId)
    {
        mDiffuseTexture = _textureId;
    }

    void Material::setSpecularTexture(const GLuint _textureId)
    {
        mSpecularTexture = _textureId;
    }

    /* Bind material textures (diffuse, specular) to the shader.
     *
     * @param { Shader* } - pointer to the shader object.
     */
    void Material::useTextures(Shader* _shader)
    {
        if(texturesSent)
            return;

        _shader->use();
        _shader->setInt("material.diffuseTexture", static_cast<GLint>(mDiffuseTexture));
        _shader->setInt("material.specularTexture", static_cast<GLint>(mSpecularTexture));
        texturesSent = true;
    }

    /* Bind material to the shader.
     *
     * @param { Shader* } - pointer to the shader object.
     */
    void Material::use(Shader* _shader)
    {
        _shader->use();
        _shader->setVec3("material.ambient", mAmbient);
        _shader->setVec3("material.diffuse", mDiffuse);
        _shader->setVec3("material.specular", mSpecular);
        _shader->setFloat("material.shininess", mShininess);
    }
}
