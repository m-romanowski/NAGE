#include "engine/render/glrenderengine.h"
#include "skybox.h"

namespace mr::nage
{
    Skybox::Skybox(const std::string& _id, Shader* _shader)
        : id_(_id),
          shader_(_shader)
    {
        vertices_ = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        setup();
    }

    Skybox::Skybox(const std::vector<float>& _vertices, Shader* _shader)
        : shader_(_shader),
          vertices_(_vertices)
    {
        setup();
    }

    Skybox::~Skybox()
    {
        delete shader_;

        glDeleteVertexArrays(1, &VAO_);
        glDeleteBuffers(1, &VBO_);

        // Clear arrays.
        faces_.clear();
        vertices_.clear();
    }

    std::string Skybox::id() const
    {
        return id_;
    }

    int Skybox::depth() const
    {
        return std::numeric_limits<int>::max();
    }

    void Skybox::setup()
    {
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);

        glBindVertexArray(VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        nage::nage_glBufferData(GL_ARRAY_BUFFER, vertices_, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    }

    void Skybox::addFacesTextures(std::vector<std::string>& _faces)
    {
        faces_ = _faces;
        textureId_ = loadCubeMap(_faces);
    }

    unsigned int Skybox::loadCubeMap(std::vector<std::string>& _faces)
    {
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        for(unsigned int i = 0; i < _faces.size(); i++)
        {
            Image image(_faces[i]);

            if(image.data())
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image.width(), image.height(), 0,
                    GL_RGB, GL_UNSIGNED_BYTE, image.data());
            }
            else
            {
                std::error_code code = ERROR::SKYBOX_FAILED_TO_LOAD_CUBMAP_TEXTURE;
                Log::error(code.message() + " " + _faces[i]);
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return id;
    }

    void Skybox::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_clipPlane);

        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::critical(code.message());

            return;
        }

        glDepthFunc(GL_LEQUAL);

        // We need transpose matrix for OpenGL (matrix column major).
        shader_->use();
        shader_->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        // Remove translation column from the view matrix.
        // We need that because we don't let get close to the edge of skybox.
        // Player will be always in the center of skybox - skybox will be not move with the camera.
        Matrix4f viewWithoutTranslation = Matrix4f::transform(Matrix4f::transform(_camera->view()));
        shader_->setMat4("view", viewWithoutTranslation.transpose());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId_);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
    }
}

//        shader_->setVec3("inColor2", 53.0f / 255.0f, 92.0f / 255.0f, 112.0f / 255.0f);
//shader_->setVec3("inColor1", 108.0f / 255.0f, 91.0f / 255.0f, 123.0f / 255.0f);
