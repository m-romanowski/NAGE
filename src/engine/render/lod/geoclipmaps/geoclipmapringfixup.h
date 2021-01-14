#ifndef NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPRINGFIXUP_H_
#define NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPRINGFIXUP_H_

#include "engine/render/renderableobject.h"

namespace mr::nage
{
    /**
     * @brief Nx3 geometry clip map ring fix-up.
     */
    class GeoClipMapRingFixUp
        : public RenderableObject
    {
    public:
        GeoClipMapRingFixUp(const float _gridSpacing, const unsigned int _gridSize, const unsigned int _n);

        Shader* shader() override { return nullptr; }
        Transform* transformation() override { return nullptr; }

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

        inline static Color color = Color(51.0f, 102.0f, 51.0f);
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPRINGFIXUP_H_
