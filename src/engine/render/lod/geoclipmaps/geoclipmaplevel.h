#ifndef NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPLEVEL_H_
#define NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPLEVEL_H_

#include "engine/generators/heightmap.h"
#include "geoclipmapblock.h"
#include "geoclipmapringfixup.h"
#include "geoclipmapinteriortrim.h"
#include "geoclipmapdegeneratetriangle.h"

#include <vector>

namespace mr::nage
{
    /**
     * @brief The GeoClipMapLevel class
     *
     * TODO: improve level components memory management (shared buffer) with one draw call.
     */
    class GeoClipMapLevel
    {
    public:
        GeoClipMapLevel(unsigned int _gridSize, unsigned int _gridSpacing, HeightMap* _heightMap, const float _maxHeight);
        ~GeoClipMapLevel();

        void create(GeoClipMapLevel* _parentLevel, GeoClipMapLevel* _childLevel);
        void render(Camera* _camera, Shader* _shader);

    private:
        void setupBlocks();
        GeoClipMapBlock* newBlock(const Vector2f _blockPosition);
        void createBlock(const Vector2f _blockPosition);
        void createCenterBlock(const Vector2f _blockPosition);
        void setupRingFixUp();
        void setupInteriorTrim();
        void setupDegenerateTriangle();
        bool isInCentral(Vector2i _currPosition);

        std::vector<GeoClipMapBlock*> blocks_; // 12 blocks
        std::vector<GeoClipMapBlock*> centerBlocks_; // 4 center blocks;
        GeoClipMapRingFixUp* ringFixUp_;
        std::vector<GeoClipMapInteriorTrim*> interiorTrim_;
        GeoClipMapDegenrateTriangle* degenerateTriangle_;

        unsigned int gridSize_, gridSpacing_;
        Vector2f minPosition_;

        GeoClipMapLevel* parentLevel_;
        GeoClipMapLevel* childLevel_;
        HeightMap* heightMap_;
        float maxHeight_;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPLEVEL_H_
