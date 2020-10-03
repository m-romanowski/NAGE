#include "material.h"

namespace mr::nage
{
    Material::Material()
        : texturesSent_(false)
    {

    }

    Material::Material(const Material& _rhs)
        : texturesSent_(false)
    {
        ambient_ = _rhs.ambient_;
        diffuse_ = _rhs.diffuse_;
        specular_ = _rhs.specular_;
        shininess_ = _rhs.shininess_;
        diffuseTexture_ = _rhs.diffuseTexture_;
        specularTexture_ = _rhs.specularTexture_;
    }

    Material::Material(const Vector3f& _ambient, const Vector3f& _diffuse, const Vector3f& _specular,
        const GLfloat _shininess)
        : ambient_(_ambient),
          diffuse_(_diffuse),
          specular_(_specular),
          shininess_(_shininess),
          texturesSent_(false)
    {

    }

    Material::Material(const Vector3f& _ambient, const Vector3f& _diffuse, const Vector3f& _specular,
        const GLfloat _shininess, const GLuint _diffuseTexture, const GLuint _specularTexture)
        : ambient_(_ambient),
          diffuse_(_diffuse),
          specular_(_specular),
          shininess_(_shininess),
          diffuseTexture_(_diffuseTexture),
          specularTexture_(_specularTexture),
          texturesSent_(false)
    {

    }

    Vector3f Material::ambient() const
    {
        return ambient_;
    }

    Vector3f Material::diffuse() const
    {
        return diffuse_;
    }

    Vector3f Material::specular() const
    {
        return specular_;
    }

    float Material::shininess() const
    {
        return shininess_;
    }

    GLuint Material::diffuseTexture() const
    {
        return diffuseTexture_;
    }

    GLuint Material::specularTexture() const
    {
        return specularTexture_;
    }

    void Material::setAmbient(const Vector3f& _ambient)
    {
        ambient_ = _ambient;
    }

    void Material::setAmbient(float _x, float _y, float _z)
    {
        ambient_ = Vector3f(_x, _y, _z);
    }

    void Material::setDiffuse(const Vector3f& _diffuse)
    {
        diffuse_ = _diffuse;
    }

    void Material::setDiffuse(float _x, float _y, float _z)
    {
        diffuse_ = Vector3f(_x, _y, _z);
    }

    void Material::setSpecular(const Vector3f& _specular)
    {
        specular_ = _specular;
    }

    void Material::setSpecular(float _x, float _y, float _z)
    {
        specular_ = Vector3f(_x, _y, _z);
    }

    void Material::setShininess(const GLfloat _shinines)
    {
        shininess_ = _shinines;
    }

    void Material::setDiffuseTexture(const GLuint _textureId)
    {
        diffuseTexture_ = _textureId;
    }

    void Material::setSpecularTexture(const GLuint _textureId)
    {
        specularTexture_ = _textureId;
    }

    /* Bind material textures (diffuse, specular) to the shader.
     *
     * @param { Shader* } - pointer to the shader object.
     */
    void Material::useTextures(Shader* _shader)
    {
        if(texturesSent_)
            return;

        _shader->use();
        _shader->setInt("material.diffuseTexture", static_cast<GLint>(diffuseTexture_));
        _shader->setInt("material.specularTexture", static_cast<GLint>(specularTexture_));
        texturesSent_ = true;
    }

    /* Bind material to the shader.
     *
     * @param { Shader* } - pointer to the shader object.
     */
    void Material::use(Shader* _shader)
    {
        _shader->use();
        _shader->setVec3("material.ambient", ambient_);
        _shader->setVec3("material.diffuse", diffuse_);
        _shader->setVec3("material.specular", specular_);
        _shader->setFloat("material.shininess", shininess_);
    }
}
