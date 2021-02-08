#ifndef NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPDEGENERATETRIANGLE_H_
#define NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPDEGENERATETRIANGLE_H_

#include "engine/render/renderableobject.h"

namespace mr::nage
{
    /**
     * @brief NxN geometry clip map block.
     */
    class GeoClipMapDegenrateTriangle
        : public RenderableObject
    {
    public:
        GeoClipMapDegenrateTriangle(const float _gridSpacin, unsigned int _gridSize);

        Shader* shader() override { return nullptr; }
        Transform* transformation() override { return nullptr; }
        Resource* resource() override { return nullptr; }

        void drawChunk(Shader* _shader, const Vector2f _levelPosition);
        std::string id() const override { return ""; }
        void useMaterials() override {}
        void bindTextures() override {}
        void unbindTextures() override {}

    private:
        void create(unsigned int _gridSize);
        void setupVertices(unsigned int _gridSize);
        void setupIndices(unsigned int _gridSize);

        float gridSpacing_;

        inline static Color color = Color(255.0f, 255.0f, 0.0f);
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPDEGENERATETRIANGLE_H_
