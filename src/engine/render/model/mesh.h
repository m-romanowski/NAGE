#ifndef NAGE_ENGINE_RENDER_MODEL_MESH_H_
#define NAGE_ENGINE_RENDER_MODEL_MESH_H_

#include "material.h"
#include "engine/render/iobject.h"
#include "engine/math/NAGEMath/nagemathcommon.h"

namespace NAGE
{
    class Mesh : public IObject
    {
    public:
        Mesh();
        explicit Mesh(const std::string& _path);
        Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        virtual ~Mesh() override;

        // Getters
        Material* material();
        Transform* transform();
        std::vector<Texture*> textures() const;

        // Setters
        void setMaterial(Material* _material);
        void addTexture(Texture* _texture);
        void setTextures(const std::vector<Texture*>& _textures);
        void setTransformation(Transform* _transform);

        void loadMesh(const std::string& _path);
        void loadMesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices);
        void bindTextures();
        void draw(Camera* _camera, Shader* _shader) override;

    protected:
        Material* mMaterial;
        Transform* mTransform;
        std::vector<Texture*> mTextures;
    };
}

#endif // NAGE_ENGINE_RENDER_MODEL_MESH_H_
