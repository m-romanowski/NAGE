#ifndef NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPBLOCK_H_
#define NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPBLOCK_H_

#include "engine/util/size.h"
#include "engine/render/renderableobject.h"

namespace mr::nage
{
    /**
     * @brief NxN geometry clip map block.
     */
    class GeoClipMapBlock
        : public RenderableObject
    {
    public:
        GeoClipMapBlock(const unsigned int _n, const float _gridSpacing, const Vector2f _gridOffset, const Vector2f _blockPosition,
            const Size<float> _elevationTextureSize);

        Shader* shader() override { return nullptr; }
        Transform* transformation() override { return nullptr; }
        Resource* resource() override { return nullptr; }

        void drawChunk(Shader* _shader, const Vector2f _levelPosition);
        std::string id() const override { return ""; }
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        void create(unsigned int _n);
        void setupVertices(unsigned int _n);
        void setupIndices(unsigned int _n);

        float gridSpacing_;
        Vector2f blockPosition_;
        Vector2f gridOffset_;
        Vector4f fineBlockOrigin_;

        inline static Color color = Color(211.0f, 211.0f, 211.0f);
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPBLOCK_H_
