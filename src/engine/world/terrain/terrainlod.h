#ifndef NAGE_ENGINE_RENDER_TERRAIN_TERRAINLOD_H_
#define NAGE_ENGINE_RENDER_TERRAIN_TERRAINLOD_H_

#include "engine/render/lod/geometryclipmap.h"

namespace NAGE
{
    class TerrainLOD
    {
    public:
        TerrainLOD();
        ~TerrainLOD();

    private:
        GeometryClipmap* mClipmap;
    };
}

#endif // NAGE_ENGINE_RENDER_TERRAIN_TERRAINLOD_H_
