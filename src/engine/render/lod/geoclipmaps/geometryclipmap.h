#ifndef NAGE_ENGINE_RENDER_LOD_GEOMETRYCLIPMAP_H_
#define NAGE_ENGINE_RENDER_LOD_GEOMETRYCLIPMAP_H_

#include "glad/glad.h"
#include "engine/render/vertex.h"

#include <vector>

#define DEFAULT_CLIPMAP_SIZE 64 // N x N vertices
#define DEFAULT_CLIPMAP_LEVELS 5 // Clipmap level depth
#define DEFAULT_CLIPMAP_SCALE 0.25 // Distance between vertices

/* TODO
 */
namespace NAGE
{
    // Geometry clipmap mesh (block, ring fixup, etc)
    class GeometryClipMapMesh
    {
    public:
        std::vector<Vertex> mVertices;
        std::vector<GLuint> mIndices;
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

        GeometryClipMapMesh mBlock;
        GeometryClipMapMesh mRingFixup;
        GeometryClipMapMesh mIteriorTrim;
        GeometryClipMapMesh mDegenerate;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOMETRYCLIPMAP_H_
