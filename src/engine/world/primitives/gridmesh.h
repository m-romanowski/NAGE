#ifndef NAGE_ENGINE_WORLD_PRIMITIVES_GRIDMESH_H_
#define NAGE_ENGINE_WORLD_PRIMITIVES_GRIDMESH_H_

#include "engine/util/size.h"
#include "engine/render/iobject.h"

namespace NAGE
{
    /* Grid mesh
     *
     * Main difference between Plane primitive and Grid mesh is that the grid
     * have only defined vertices and indices (without any shader, mesh transformation) -
     * - pure mesh grid, like IObject interface
     */
    class GridMesh : public IObject
    {
    public:
        GridMesh(const Size<int> _size);
        GridMesh(int _width, int _height);

        // Getters
        int width() const;
        int height() const;
        Size<int> size() const;

        // Setters
        void setWidth(int _width);
        void setHeight(int _height);
        void setSize(const Size<int> _size);

        virtual void setupMeshBuffers();

    protected:
        int mWidth, mHeight;
    };
}

#endif // NAGE_ENGINE_WORLD_PRIMITIVES_GRIDMESH_H_
