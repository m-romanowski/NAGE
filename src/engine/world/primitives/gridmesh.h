#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_GRIDMESH_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_GRIDMESH_H_

#include "engine/util/size.h"
#include "engine/render/renderableobject.h"

namespace mr::nage
{
    /* Grid mesh
     *
     * Main difference between Plane primitive and Grid mesh is that the grid
     * have only defined vertices and indices (without any shader, mesh transformation) -
     * - pure mesh grid, like RenderableObject interface
     */
    class GridMesh
        : public RenderableObject
    {
    public:
        GridMesh(const std::string& _id, const Size<int> _size);
        GridMesh(const std::string& _id, int _width, int _height);

        // Getters
        int width() const;
        int height() const;
        Size<int> size() const;
        Shader* shader() override { return nullptr; }
        Transform* transformation() override { return nullptr; }
        Resource* resource() override { return nullptr; }

        // Setters
        void setWidth(int _width);
        void setHeight(int _height);
        void setSize(const Size<int> _size);

        std::string id() const override;
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}
        virtual void setupMeshBuffers();

    protected:
        std::string id_;
        int width_, height_;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_GRIDMESH_H_
