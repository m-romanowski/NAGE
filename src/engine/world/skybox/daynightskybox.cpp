#include "engine/render/glrenderengine.h"
#include "daynightskybox.h"

namespace mr::nage
{
    DayNightSkybox::DayNightSkybox(const std::string& _id, Shader* _shader)
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

        // Setup day-night cycle color map.
        _shader->use();
        _shader->setVec3("cycle.morning", TimeOfDay::fromColor(TimeOfDay::colorFor(TimeOfDay::TimeOfDayType::Morning)));
        _shader->setVec3("cycle.midday", TimeOfDay::fromColor(TimeOfDay::colorFor(TimeOfDay::TimeOfDayType::Midday)));
        _shader->setVec3("cycle.evening", TimeOfDay::fromColor(TimeOfDay::colorFor(TimeOfDay::TimeOfDayType::Evening)));
        _shader->setVec3("cycle.midnight", TimeOfDay::fromColor(TimeOfDay::colorFor(TimeOfDay::TimeOfDayType::Midnight)));

        // Default time supplier.
        timeSupplier_ = []() -> Time {
            time_t now = time(0);
            tm* ltm = localtime(&now);

            int hour = ltm->tm_hour;
            int min = ltm->tm_min;
            int sec = ltm->tm_sec;

            return Time(hour, min, sec);
        };

        setup();
    }

    DayNightSkybox::DayNightSkybox(const std::vector<float>& _vertices, Shader* _shader)
        : shader_(_shader),
          vertices_(_vertices)
    {
        setup();
    }

    DayNightSkybox::~DayNightSkybox()
    {
        delete shader_;

        glDeleteVertexArrays(1, &VAO_);
        glDeleteBuffers(1, &VBO_);

        // Clear arrays.
        vertices_.clear();
    }

    std::string DayNightSkybox::id() const
    {
        return id_;
    }

    int DayNightSkybox::depth() const
    {
        return std::numeric_limits<int>::max();
    }

    void DayNightSkybox::setup()
    {
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);

        glBindVertexArray(VAO_);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        nage::nage_glBufferData(GL_ARRAY_BUFFER, vertices_, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    }

    void DayNightSkybox::draw(Camera* _camera, const Vector4f _clipPlane)
    {
        NAGE_UNUSED(_clipPlane);

        if(!shader_)
        {
            std::error_code code = ERROR::SHADER_FAILED_TO_FIND_PROGRAM;
            Log::critical(code.message());

            return;
        }

        glDepthFunc(GL_LEQUAL);

        // Get current time.
        Time now = timeSupplier_();

        // We need transpose matrix for OpenGL (matrix column major).
        shader_->use();
        shader_->setFloat("cycle.startStep", START_STEP);
        shader_->setFloat("cycle.stopStep", STOP_STEP);
        shader_->setInt("cycle.hour", now.hour);
        shader_->setInt("cycle.minute", now.minute);
        shader_->setMat4("projection", GLRenderEngine::projection().perspective().transpose());
        // Remove translation column from the view matrix.
        // We need that because we don't let get close to the edge of skybox.
        // Player will be always in the center of skybox - skybox will be not move with the camera.
        Matrix4f viewWithoutTranslation = Matrix4f::transform(Matrix4f::transform(_camera->view()));
        shader_->setMat4("view", viewWithoutTranslation.transpose());

        // Draw mesh.
        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
    }
}
