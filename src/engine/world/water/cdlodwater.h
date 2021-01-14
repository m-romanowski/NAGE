#ifndef NAGE_ENGINE_WORLD_WATER_CDLODWATER_H_
#define NAGE_ENGINE_WORLD_WATER_CDLODWATER_H_

#include "iwater.h"
#include "engine/render/lod/cdlod/icdlodobject.h"
#include "engine/render/model/material.h"
#include "engine/render/lod/cdlod/cdlod.h"
#include "engine/render/culling/frustumculling.h"

#include <map>

namespace mr::nage
{
    class CDLODWater : public ICDLODObject, public IWater
    {
    public:
        CDLODWater(const std::string& _id, int _lodLevel, HeightMap* _heightmap, CDLODSettings _settins = CDLODSettings());
        ~CDLODWater();

        void draw(Camera* _camera, const Vector4f _clipPlane) override;
    };
}

#endif // NAGE_ENGINE_WORLD_WATER_CDLODWATER_H_
