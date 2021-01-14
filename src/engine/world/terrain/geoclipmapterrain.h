#ifndef NAGE_ENGINE_WORLD_TERRAIN_GEOCLIPMAPTERRAIN_H_
#define NAGE_ENGINE_WORLD_TERRAIN_GEOCLIPMAPTERRAIN_H_

#include "engine/generators/heightmap.h"
#include "engine/render/lod/geoclipmaps/geoclipmaplod.h"
#include "engine/render/model/material.h"
#include "iterrain.h"

namespace mr::nage
{
    class GeoClipMapTerrain
        : public GeoClipMapLOD, public ITerrain
    {
    public:
        GeoClipMapTerrain(const std::string& _id, HeightMap* _heightmap, const float _maxHeight, const unsigned int _levels = 1);
        ~GeoClipMapTerrain();

        void draw(Camera* _camera, const Vector4f _clipPlane) override;
    };
}

#endif // NAGE_ENGINE_WORLD_TERRAIN_GEOCLIPMAPTERRAIN_H_
