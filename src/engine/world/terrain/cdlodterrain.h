#ifndef NAGE_ENGINE_WORLD_TERRAIN_CDLODTERRAIN_H_
#define NAGE_ENGINE_WORLD_TERRAIN_CDLODTERRAIN_H_

#include "iterrain.h"
#include "cdlodterrainchunk.h"
#include "engine/render/model/material.h"
#include "engine/render/lod/cdlod/cdlod.h"
#include "engine/render/culling/frustumculling.h"

#include <map>

#define DEFAULT_TERRAIN_CDLOD_CHUNKS_COUNT 7

namespace NAGE
{
    class CDLODTerrain : public ITerrain
    {
    public:
        CDLODTerrain(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settins = CDLODSettings());
        ~CDLODTerrain();

        // Getters
        int lodLevel() const;
        float maxHeight() const;
        unsigned int chunkCount() const;
        CDLOD* lod();
        std::map<int, CDLODTerrainChunk*> chunks() const;
        CDLODTerrainChunk* chunk(int _dimension);
        HeightMap* heightMap();

        // Setters
        void setMaxHeight(float _height);

        void useHeightMapTexture();
        void bindTextures() override;
        void render(Camera* _camera) override;

    private:
        int mLodLevel;
        float mMaxHeight;
        CDLOD* mLOD;
        FrustumCulling* mFrustum;
        HeightMap* mHeightMap;
        std::map<int, CDLODTerrainChunk*> mTerrainChunks; // key: dimension, value: chunk grid
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_CDLODTERRAIN_H_
