#ifndef NAGE_ENGINE_RENDER_SHADER_H_
#define NAGE_ENGINE_RENDER_SHADER_H_

#include "glad/glad.h"

#include "common/log.h"
#include "common/errormanager.h"
#include "engine/components/const.h"
#include "engine/math/NAGEMath/nagemathvector.h"
#include "engine/math/NAGEMath/nagemathmatrix.h"
#include "engine/math/NAGEMath/nagemathquaternion.h"

#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

namespace NAGE
{
    enum SHADER_TYPE
    {
        SHADER_VERTEX,
        SHADER_FRAGMENT,
        SHADER_GEOMETRY,
        SHADER_PROGRAM
    };

    class Shader
    {
    public:
        Shader();

        // Uniforms.
        void setBool(const std::string& _name, GLboolean _value) const;
        void setInt(const std::string& _name, GLint _value) const;
        void setFloat(const std::string& _name, GLfloat _value) const;
        void setVec2(const std::string& _name, GLfloat _x, GLfloat _y) const;
        void setVec2(const std::string& _name, const Vector2f& _value) const;
        void setVec3(const std::string& _name, GLfloat _x, GLfloat _y, GLfloat _z) const;
        void setVec3(const std::string& _name, const Vector3f& _value) const;
        void setVec4(const std::string& _name, GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w) const;
        void setVec4(const std::string& _name, const Quaternion& _value) const;
        void setMat2(const std::string& _name, const Matrix2f& _value) const;
        void setMat3(const std::string& _name, const Matrix3f& _value) const;
        void setMat4(const std::string& _name, const Matrix4f& _value) const;

        // Getters.
        GLuint id();

        void use();
        void link();
        void addShaderFromSourceCode(SHADER_TYPE _type, const std::string& _source);
        void addShaderFromSourceFile(SHADER_TYPE _type, const std::string& _path);

    private:
        void readShaderFiles(const char* _vertexPath, const char* _fragmentPath, const char* _geometryPath = nullptr);
        void compileShader(SHADER_TYPE _type, const char* _shaderCode);
        void checkCompileErrors(GLuint _shader, SHADER_TYPE _type);

        // Shader program id.
        GLuint id_, vertexObj_, fragmentObj_, geometryObj_;
    };
}

#endif // NAGE_ENGINE_RENDER_SHADER_H_
