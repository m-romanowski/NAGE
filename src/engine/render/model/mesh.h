#ifndef NAGE_ENGINE_RENDER_MODEL_MESH_H_
#define NAGE_ENGINE_RENDER_MODEL_MESH_H_

#include "material.h"
#include "engine/render/renderableobject.h"
#include "engine/math/NAGEMath/nagemathcommon.h"

namespace mr::nage
{
    class Model;

    class Mesh
        : public RenderableObject
    {
    public:
        Mesh(const std::string& _id, Model* _parent);
        Mesh(const std::string& _id, const std::string& _path, Model* _parent);
        Mesh(const std::string& _id, const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices, Model* _parent);
        ~Mesh() override;

        // Getters
        Material* material();
        std::vector<Texture*> textures() const;
        bool isChild(Model* _model);
        Shader* shader() override { return nullptr; }
        Transform* transformation() override;
        Resource* resource() override { return nullptr; } // TODO

        // Setters
        void setMaterial(Material* _material);
        void addTexture(Texture* _texture);
        void setTextures(const std::vector<Texture*>& _textures);
        void setTransformation(Transform* _transform);
        void setParent(Model* _parent);

        void loadMesh(const std::string& _path);
        void loadMesh(const std::vector<Vertex>& _vertices, const std::vector<GLuint>& _indices);
        std::string id() const override;
        void useMaterials() override {}
        void bindTextures() override;
        void unbindTextures() override;
        void draw(Camera* _camera, const Vector4f _clipPlane) override;

    protected:
        std::string id_;
        Material* material_;
        Transform* transform_;
        std::vector<Texture*> textures_;
        Model* parent_;
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_MESH_H_
