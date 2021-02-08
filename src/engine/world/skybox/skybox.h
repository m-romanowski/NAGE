#ifndef NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_
#define NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_

#include "engine/render/renderableobject.h"
#include "engine/render/shader.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/components/image.h"
#include "engine/components/camera/camera.h"

#include <vector>
#include <string>

namespace mr::nage
{
    class Skybox
        : public RenderableObject
    {
    public:
        Skybox(const std::string& _id, Shader* _shader);
        Skybox(const std::vector<float>& _vertices, Shader* _shader);
        ~Skybox();

        // Getters
        inline unsigned int textureID() const { return textureId_; }
        inline std::vector<std::string> faces() const { return faces_; }
        inline std::vector<float> vertices() const { return vertices_; }
        inline Shader* shader() override { return shader_; }
        inline Transform* transformation() override { return nullptr; }
        Resource* resource() override { return nullptr; }

        // Setters
        inline void setShader(Shader* _shader) { shader_ = _shader; }
        inline void setVertices(const std::vector<float>& _vertices) { vertices_ = _vertices; }
        void addFacesTextures(std::vector<std::string>& _faces);

        std::string id() const override;
        void draw(Camera* _camera, const Vector4f _clipPlane) override;
        int depth() const override;
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        void setup();
        unsigned int loadCubeMap(std::vector<std::string>& _faces);

        std::string id_;
        unsigned int VAO_, VBO_;
        unsigned int textureId_;
        Shader* shader_;
        std::vector<std::string> faces_;
        std::vector<float> vertices_;
    };
}

#endif // NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_
