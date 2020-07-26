#ifndef NAGE_ENGINE_RENDER_MODEL_MODEL_H_
#define NAGE_ENGINE_RENDER_MODEL_MODEL_H_

#include "mesh.h"
#include "material.h"
#include "engine/world/primitives/primitive.h"

namespace NAGE
{
    class Model
    {
    public:
        Model();
        explicit Model(Primitive& _primitive);
        ~Model();

        // Getters
        std::vector<Mesh*> meshes() const;
        Transform* transformation();
        Shader* shader();

        // Setters
        void addMesh(Mesh* _mesh);
        void addMesh(const std::string& _path);
        void addMesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        void setMeshes(const std::vector<Mesh*>& _meshes);
        void setTransformation(Transform* _transform);
        void setShader(Shader* _shader);

        void useMaterials();
        void bindTextures();
        void unbindTextures();
        void draw(Camera* _camera, Vector4f _clipPlane);
        void loadModel(const std::string& _path);

    protected:
        std::vector<Mesh*> mMeshes;
        Transform* mTransform;
        Shader* mShader;
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_MODEL_H_
