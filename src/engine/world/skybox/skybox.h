#ifndef NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_
#define NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_

#include "engine/render/shader.h"
#include "engine/wrapper/glwrapper.h"
#include "engine/components/image.h"
#include "engine/components/camera/camera.h"

#include <vector>
#include <string>

namespace NAGE
{
    class Skybox
    {
    public:
        Skybox(Shader* _shader);
        Skybox(const std::vector<float>& _vertices, Shader* _shader);
        ~Skybox();

        // Getters
        inline Shader* shader() { return mShader; }
        inline unsigned int textureID() const { return mTextureID; }
        inline std::vector<std::string> faces() const { return mFaces; }
        inline std::vector<float> vertices() const { return mVertices; }

        // Setters
        inline void setShader(Shader* _shader) { mShader = _shader; }
        inline void setVertices(const std::vector<float>& _vertices) { mVertices = _vertices; }
        void addFacesTextures(std::vector<std::string>& _faces);

        void draw(Camera& _camera);
    private:
        void setup();
        unsigned int loadCubeMap(std::vector<std::string>& _faces);

        unsigned int mVAO, mVBO;
        unsigned int mTextureID;
        Shader* mShader;
        std::vector<std::string> mFaces;
        std::vector<float> mVertices;
    };
}

#endif // NAGE_ENGINE_RENDER_SKYBOX_SKYBOX_H_
