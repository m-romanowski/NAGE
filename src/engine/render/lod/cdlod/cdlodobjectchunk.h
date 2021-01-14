#ifndef NAGE_ENGINE_RENDER_LOD_CDLODOBJECTCHUNK_H_
#define NAGE_ENGINE_RENDER_LOD_CDLODOBJECTCHUNK_H_

#include "engine/render/renderableobject.h"

namespace mr::nage
{
    class CDLODObjectChunk
        : public RenderableObject
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
        Shader* shader() override { return nullptr; }
        Transform* transformation() override { return nullptr; }

        void drawChunk(int _indicesCount, int _indicesIndexLocation);
        std::string id() const override { return ""; }
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        void appendIndices(int _x, int _z, int _size, int& _currentOffset);

        // Indices index (when we want render a partial grid - one of quads).
        int topLeftEndIndex_;
        int topRightEndIndex_;
        int bottomLeftEndIndex_;
        int bottomRightEndIndex_;

        int size_;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLODOBJECTCHUNK_H_
