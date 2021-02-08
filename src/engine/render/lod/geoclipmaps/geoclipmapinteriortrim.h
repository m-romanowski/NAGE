#ifndef NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPINTERIORTRIM_H_
#define NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPINTERIORTRIM_H_

#include "engine/render/renderableobject.h"

namespace mr::nage
{
    /**
     * @brief NxN geometry clip map block.
     */
    class GeoClipMapInteriorTrim
        : public RenderableObject
    {
    public:
        GeoClipMapInteriorTrim(const float _gridSpacing, unsigned int _gridSize, unsigned int _n);

        Shader* shader() override { return nullptr; }
        Transform* transformation() override { return nullptr; }
        Resource* resource() override { return nullptr; }

        void drawChunk(Shader* _shader, const Vector2f _levelPosition);
        std::string id() const override { return ""; }
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        void create(unsigned int _gridSize, unsigned int _n);
        void setupVertices(unsigned int _gridSize, unsigned int _n);
        void setupIndices(unsigned int _n);

        float gridSpacing_;

        inline static Color color = Color(76.0f, 0.0f, 153.0f);

        // TODO: interrior trim for each side (top-left, top-right, bottom-left, bottom-right).
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPINTERIORTRIM_H_
