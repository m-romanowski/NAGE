#include "engine/render/glrenderengine.h"
#include "daynightskydome.h"

namespace mr::nage
{
    DayNightSkydome::DayNightSkydome(const std::string& _id, Shader* _shader, SunLight* _sun, float _radius)
        : Sphere(_id, 36, 18, _radius),
          atmosphereRadius_(_radius + 100000),
          sun_(_sun)
    {
        setShader(_shader);
        setupBuffer();
    }

    int DayNightSkydome::depth() const
    {
        return std::numeric_limits<int>::max();
    }

    void DayNightSkydome::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_clipPlane);

        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::fatal(code.message());

            return;
        }

        glDepthFunc(GL_LEQUAL);

        // We need transpose matrix for OpenGL (matrix column major).
        shader_->use();

        shader_->setVec3("cameraPosition", _camera->translation());
        shader_->setFloat("g", 0.758);
        shader_->setFloat("Re", radius_);
        shader_->setFloat("Ra", atmosphereRadius_);
        shader_->setInt("nSamples", 16);
        shader_->setInt("nLightSamples", 8);
        shader_->setVec3("sunPosition", sun_->transformation()->translation());
        shader_->setFloat("sunIntensity", 20.0f);
        shader_->setFloat("Hr", 8500); // Earth scale height
        shader_->setFloat("Hm", 1200); // Mie height scale
        shader_->setVec3("betaR", Vector3f(5.5e-6, 13.0e-6, 22.4e-6));
        shader_->setFloat("betaM", 21e-6);

        shader_->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        // Remove translation column from the view matrix.
        // We need that because we don't let get close to the edge of skybox.
        // Player will be always in the center of skybox - skybox will be not move with the camera.
        Matrix4f viewWithoutTranslation = Matrix4f::transform(Matrix4f::transform(_camera->view()));
        shader_->setMat4("view", viewWithoutTranslation.transpose());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT,
            reinterpret_cast<void*>(0));
        glDepthFunc(GL_LESS);
    }
}
