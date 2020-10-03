#ifndef NAGE_ENGINE_RENDER_LOD_GEOMETRYCLIPMAP_H_
#define NAGE_ENGINE_RENDER_LOD_GEOMETRYCLIPMAP_H_

#include "glad/glad.h"
#include "engine/render/vertex.h"

#include <vector>

#define DEFAULT_CLIPMAP_SIZE 64 // N x N vertices
#define DEFAULT_CLIPMAP_LEVELS 5 // Clipmap level depth
#define DEFAULT_CLIPMAP_SCALE 0.25 // Distance between vertices

/**
 * TODO
 */
namespace mr::nage
{
    // Geometry clipmap mesh (block, ring fixup, degenerate)
    class GeometryClipMapMesh
    {
    public:
        std::vector<Vertex> vertices_;
        std::vector<GLuint> indices_;
    };

    class GeometryClipmap
    {
    public:
        GeometryClipmap();

        void setupBuffers(int _size);

    private:
        void setupBlock(unsigned int _n);
        void setupRingFixup(unsigned int _m, unsigned int _n);
        void setupInteriorTrim(unsigned int _size);
        void setupDegenerate(unsigned int _size);

        GeometryClipMapMesh block_;
        GeometryClipMapMesh ringFixup_;
        GeometryClipMapMesh iteriorTrim_;
        GeometryClipMapMesh degenerate_;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOMETRYCLIPMAP_H_
