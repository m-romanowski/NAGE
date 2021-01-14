#ifndef NAGE_ENGINE_RENDER_MODEL_MODEL_H_
#define NAGE_ENGINE_RENDER_MODEL_MODEL_H_

#include "mesh.h"
#include "material.h"
#include "engine/world/primitives/primitive.h"

namespace mr::nage
{
    class Model
        : public RenderableObject
    {
    public:
        Model(const std::string& _id);
        explicit Model(Primitive& _primitive);
        ~Model();

        // Getters
        std::vector<Mesh*> meshes() const;
        Shader* shader() override;
        Transform* transformation() override;

        // Setters
        void addMesh(Mesh* _mesh);
        void addMesh(const std::string& _path);
        void addMesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        void setMeshes(const std::vector<Mesh*>& _meshes);
        void setTransformation(Transform* _transform);
        void setShader(Shader* _shader);

        void loadModel(const std::string& _path);
        std::string id() const override;
        void useMaterials() override;
        void bindTextures() override;
        void unbindTextures() override;
        void draw(Camera* _camera, const Vector4f _clipPlane) override;

    protected:
        std::string id_;
        std::vector<Mesh*> meshes_;
        Transform* transform_;
        Shader* shader_;
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_MODEL_H_
