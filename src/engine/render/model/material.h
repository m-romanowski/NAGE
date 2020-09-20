#ifndef NAGE_ENGINE_RENDER_MODEL_MATERIAL_H_
#define NAGE_ENGINE_RENDER_MODEL_MATERIAL_H_

#include "glad/glad.h"
#include "engine/render/shader.h"
#include "engine/math/NAGEMath/nagemathvector.h"

namespace NAGE
{
    class Material
    {
    public:
        Material();
        Material(const Material& _rhs);
        Material(const Vector3f& _ambient, const Vector3f& _diffuse,
            const Vector3f& _specular, const GLfloat _shininess);
        Material(const Vector3f& _ambient, const Vector3f& _diffuse,
            const Vector3f& _specular, const GLfloat _shininess,
            const GLuint _diffuseTexture, const GLuint _specularTexture);

        // Getters
        Vector3f ambient() const;
        Vector3f diffuse() const;
        Vector3f specular() const;
        GLfloat shininess() const;
        GLuint diffuseTexture() const;
        GLuint specularTexture() const;

        // Setters
        void setAmbient(const Vector3f& _ambient);
        void setAmbient(float _x, float _y, float _z);
        void setDiffuse(const Vector3f& _diffuse);
        void setDiffuse(float _x, float _y, float _z);
        void setSpecular(const Vector3f& _specular);
        void setSpecular(float _x, float _y, float _z);
        void setShininess(const GLfloat _shinines);
        void setDiffuseTexture(const GLuint _textureId);
        void setSpecularTexture(const GLuint _textureId);

        void use(Shader* _shader);
        void useTextures(Shader* _shader);

    private:
        Vector3f ambient_;
        Vector3f diffuse_;
        Vector3f specular_;
        GLfloat shininess_;
        GLuint diffuseTexture_;
        GLuint specularTexture_;

        bool texturesSent_;
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_MATERIAL_H_
