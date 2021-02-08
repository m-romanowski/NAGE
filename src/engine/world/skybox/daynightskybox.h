#ifndef NAGE_ENGINE_RENDER_SKYBOX_DAYNIGHTSKYBOX_H_
#define NAGE_ENGINE_RENDER_SKYBOX_DAYNIGHTSKYBOX_H_

#include "engine/render/renderableobject.h"
#include "engine/render/shader.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/components/image.h"
#include "engine/components/camera/camera.h"

#include <string>

namespace mr::nage
{
    class DayNightSkybox
        : public RenderableObject
    {
        struct TimeOfDay
        {
        public:
            enum class TimeOfDayType
            {
                Dawn,
                Morning,
                Midday,
                Evening,
                Midnight
            };

            static Color colorFor(TimeOfDayType _type)
            {
                switch(_type)
                {
                    case TimeOfDayType::Dawn:
                        return Color(248.0f, 177.0f, 149.0f);
                    case TimeOfDayType::Morning:
                        return Color(108.0f, 91.0f, 123.0f);
                    case TimeOfDayType::Midday:
                        return Color(53.0f, 92.0f, 112.0f);
                    case TimeOfDayType::Evening:
                        return Color(246.0f, 114.0f, 128.0f);
                    case TimeOfDayType::Midnight:
                        return Color(14.0f, 23.0f, 28.0f);
                    default:
                        throw new std::runtime_error("Unsupported type");
                }
            }

            static Vector3f fromColor(const Color _color)
            {
                return Vector3f(_color.red(), _color.green(), _color.blue());
            }
        };

    public:
        struct Time
        {
            unsigned short hour;
            unsigned short minute;
            unsigned short second;

            Time(const unsigned short _hour, const unsigned short _minute, const unsigned short _second)
            {
                this->hour = _hour;
                this->minute = _minute;
                this->second = _second;
            }
        };

    public:
        DayNightSkybox(const std::string& _id, Shader* _shader);
        DayNightSkybox(const std::vector<float>& _vertices, Shader* _shader);
        ~DayNightSkybox();

        // Getters
        inline std::vector<float> vertices() const { return vertices_; }
        inline Shader* shader() override { return shader_; }
        inline Transform* transformation() override { return nullptr; }
        Resource* resource() override { return nullptr; }

        // Setters
        inline void setShader(Shader* _shader) { shader_ = _shader; }
        inline void setVertices(const std::vector<float>& _vertices) { vertices_ = _vertices; }
        inline void setTimeSupplier(const std::function<Time()> _supplier) { timeSupplier_ = _supplier; }

        std::string id() const override;
        void draw(Camera* _camera, const Vector4f _clipPlane) override;
        int depth() const override;
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        void setup();

        std::string id_;
        unsigned int VAO_, VBO_;
        Shader* shader_;
        std::vector<float> vertices_;

        std::function<Time()> timeSupplier_;

        inline static const constexpr float START_STEP = -1.0f;
        inline static const constexpr float STOP_STEP = 0.5f;
    };
}

#endif // NAGE_ENGINE_RENDER_SKYBOX_DAYNIGHTSKYBOX_H_
