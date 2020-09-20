#include "shader.h"

namespace NAGE
{
    Shader::Shader()
        : vertexObj_(0),
          fragmentObj_(0),
          geometryObj_(0)
    {

    }

    GLuint Shader::id()
    {
        return id_;
    }

    void Shader::addShaderFromSourceCode(SHADER_TYPE _type, const std::string& _source)
    {
        compileShader(_type, _source.c_str());
    }

    void Shader::addShaderFromSourceFile(SHADER_TYPE _type, const std::string& _path)
    {
        std::ifstream shaderFile;
        std::string shaderCode;

        // Exceptions
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        // Open file
        try
        {
            // Open shader files (vertex, fragment).
            shaderFile.open(_path);

            // Save file buffer to stream.
            std::stringstream shaderFileStream;
            shaderFileStream << shaderFile.rdbuf();

            // Close file handlers.
            shaderFile.close();

            // Convert stream into chars.
            shaderCode = shaderFileStream.str();
        }
        catch(std::ifstream::failure& error)
        {
            std::error_code code = ERROR::SHADER_FAILED_FILE_READ;
            Log::error(code.message() + " What: " + error.what());

            return;
        }

        compileShader(_type, shaderCode.c_str());
    }

    void Shader::compileShader(SHADER_TYPE _type, const char* _shaderCode)
    {
        switch(_type)
        {
            case SHADER_TYPE::SHADER_VERTEX:
                vertexObj_ = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexObj_, 1, &_shaderCode, nullptr);
                glCompileShader(vertexObj_);
                checkCompileErrors(vertexObj_, SHADER_TYPE::SHADER_VERTEX);
                break;
            case SHADER_TYPE::SHADER_FRAGMENT:
                fragmentObj_ = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentObj_, 1, &_shaderCode, nullptr);
                glCompileShader(fragmentObj_);
                checkCompileErrors(fragmentObj_, SHADER_TYPE::SHADER_FRAGMENT);
                break;
            case SHADER_TYPE::SHADER_GEOMETRY:
                geometryObj_ = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geometryObj_, 1, &_shaderCode, nullptr);
                glCompileShader(geometryObj_);
                checkCompileErrors(geometryObj_, SHADER_TYPE::SHADER_GEOMETRY);
                break;
            case SHADER_TYPE::SHADER_PROGRAM:
                break;
        }
    }

    void Shader::link()
    {
        if(!vertexObj_ || !fragmentObj_)
        {
            std::error_code code = ERROR::SHADER_FAILED_LINKING;
            Log::error(code.message());

            return;
        }

        // Program object
        id_ = glCreateProgram();
        glAttachShader(id_, vertexObj_);
        glAttachShader(id_, fragmentObj_);
        if(geometryObj_) glAttachShader(id_, geometryObj_);

        // Link program
        glLinkProgram(id_);

        // Check linking errors.
        checkCompileErrors(id_, SHADER_TYPE::SHADER_PROGRAM);

        // Delete shader objects.
        glDeleteShader(vertexObj_);
        glDeleteShader(fragmentObj_);
        if(geometryObj_) glDeleteShader(geometryObj_);
    }

    void Shader::checkCompileErrors(GLuint _object, SHADER_TYPE _type)
    {
        int success;
        char infoLog[1024];

        if((_type == SHADER_TYPE::SHADER_VERTEX) || (_type == SHADER_TYPE::SHADER_FRAGMENT) ||
            (_type == SHADER_TYPE::SHADER_GEOMETRY))
        {
            // Compilation error
            glGetShaderiv(_object, GL_COMPILE_STATUS, &success);

            if(!success)
            {
                glGetShaderInfoLog(_object, 1024, nullptr, infoLog);

                std::error_code code = ERROR::SHADER_FAILED_COMPILATION;
                Log::error(code.message() + " " + infoLog);

                return;
            }
        }
        else if(_type == SHADER_TYPE::SHADER_PROGRAM)
        {
            glGetProgramiv(_object, GL_LINK_STATUS, &success);

            if(!success)
            {
                glGetProgramInfoLog(_object, 1024, nullptr, infoLog);
                std::error_code code = ERROR::SHADER_FAILED_LINKING;
                Log::error(code.message() + " " + infoLog);

                return;
            }
        }
        else
        {
            std::error_code code = ERROR::SHADER_UNEXPECTED_TYPE;
            Log::error(code.message());
        }
    }

    void Shader::use()
    {
        glUseProgram(id_);
    }

    void Shader::setBool(const std::string& _name, GLboolean _value) const
    {
        glUniform1i(glGetUniformLocation(id_, _name.c_str()), static_cast<int>(_value));
    }

    void Shader::setInt(const std::string& _name, GLint _value) const
    {
        glUniform1i(glGetUniformLocation(id_, _name.c_str()), _value);
    }

    void Shader::setFloat(const std::string& _name, GLfloat _value) const
    {
        glUniform1f(glGetUniformLocation(id_, _name.c_str()), _value);
    }

    void Shader::setVec2(const std::string& _name, GLfloat _x, GLfloat _y) const
    {
        glUniform2f(glGetUniformLocation(id_, _name.c_str()), _x, _y);
    }

    void Shader::setVec2(const std::string& _name, const Vector2f& _value) const
    {
        glUniform2fv(glGetUniformLocation(id_, _name.c_str()), 1, reinterpret_cast<const GLfloat*>(&_value));
    }

    void Shader::setVec3(const std::string& _name, GLfloat _x, GLfloat _y, GLfloat _z) const
    {
        glUniform3f(glGetUniformLocation(id_, _name.c_str()), _x, _y, _z);
    }

    void Shader::setVec3(const std::string& _name, const Vector3f& _value) const
    {
        glUniform3fv(glGetUniformLocation(id_, _name.c_str()), 1, reinterpret_cast<const GLfloat*>(&_value));
    }

    void Shader::setVec4(const std::string& _name, GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w) const
    {
        glUniform4f(glGetUniformLocation(id_, _name.c_str()), _x, _y, _z, _w);
    }

    void Shader::setVec4(const std::string& _name, const Quaternion& _value) const
    {
        glUniform4fv(glGetUniformLocation(id_, _name.c_str()), 1, reinterpret_cast<const GLfloat*>(&_value));
    }

    void Shader::setMat2(const std::string& _name, const Matrix2f& _value) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id_, _name.c_str()), 1, GL_FALSE, &_value(0, 0));
    }

    void Shader::setMat3(const std::string& _name, const Matrix3f& _value) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id_, _name.c_str()), 1, GL_FALSE, &_value(0, 0));
    }

    void Shader::setMat4(const std::string& _name, const Matrix4f& _value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id_, _name.c_str()), 1, GL_FALSE, &_value(0, 0));
    }
}
