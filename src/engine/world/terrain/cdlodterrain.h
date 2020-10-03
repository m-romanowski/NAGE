#ifndef NAGE_ENGINE_WORLD_TERRAIN_CDLODTERRAIN_H_
#define NAGE_ENGINE_WORLD_TERRAIN_CDLODTERRAIN_H_

#include "iterrain.h"
#include "engine/render/lod/cdlod/icdlodobject.h"
#include "engine/render/model/material.h"
#include "engine/render/lod/cdlod/cdlod.h"
#include "engine/render/culling/frustumculling.h"

#include <map>

namespace mr::nage
{
    class CDLODTerrain : public ICDLODObject, public ITerrain
    {
    public:
        CDLODTerrain(int _lodLevel, HeightMap* _heightmap, CDLODSettings _settins = CDLODSettings());
        ~CDLODTerrain();

        void render(Camera* _camera, Vector4f _clipPlane) override;
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_CDLODTERRAIN_H_
