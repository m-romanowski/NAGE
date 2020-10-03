#ifndef NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_
#define NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_

#include "engine/render/shader.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/components/image.h"
#include "engine/components/camera/camera.h"

#include <vector>
#include <string>

namespace mr::nage
{
    class Skybox
    {
    public:
        Skybox(Shader* _shader);
        Skybox(const std::vector<float>& _vertices, Shader* _shader);
        ~Skybox();

        // Getters
        inline Shader* shader() { return shader_; }
        inline unsigned int textureID() const { return textureId_; }
        inline std::vector<std::string> faces() const { return faces_; }
        inline std::vector<float> vertices() const { return vertices_; }

        // Setters
        inline void setShader(Shader* _shader) { shader_ = _shader; }
        inline void setVertices(const std::vector<float>& _vertices) { vertices_ = _vertices; }
        void addFacesTextures(std::vector<std::string>& _faces);

        void draw(Camera* _camera);

    private:
        void setup();
        unsigned int loadCubeMap(std::vector<std::string>& _faces);

        unsigned int VAO_, VBO_;
        unsigned int textureId_;
        Shader* shader_;
        std::vector<std::string> faces_;
        std::vector<float> vertices_;
    };
}

#endif // NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_
