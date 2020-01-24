#ifndef NAGE_ENGINE_RENDER_LOD_CDLODOBJECTCHUNK_H_
#define NAGE_ENGINE_RENDER_LOD_CDLODOBJECTCHUNK_H_

#include "engine/render/iobject.h"

namespace NAGE
{
    class CDLODObjectChunk : public IObject
    {
    public:
        CDLODObjectChunk(int _size);

        void setupMeshBuffers();

        // Getters
        int topLeftEndIndex() const;
        int topRightEndIndex() const;
        int bottomLeftEndIndex() const;
        int bottomRightEndIndex() const;
        int size() const;

        void drawChunk(int _indicesCount, int _indicesIndexLocation);

    private:
        void appendIndices(int _x, int _z, int _size, int& _currentOffset);

        // Indices index (when we want render a partial grid - one of quads).
        int mTopLeftEndIndex;
        int mTopRightEndIndex;
        int mBottomLeftEndIndex;
        int mBottomRightEndIndex;

        int mSize;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLODOBJECTCHUNK_H_
