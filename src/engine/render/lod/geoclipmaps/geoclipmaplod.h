#ifndef NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPLOD_H_
#define NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPLOD_H_

#include "geoclipmaplevel.h"

namespace mr::nage
{
    class GeoClipMapLOD
    {
        typedef std::unique_ptr<GeoClipMapLevel> level_uptr;

    public:
        GeoClipMapLOD(const unsigned int _levels, HeightMap* _heightMap, const float _maxHeight);
        ~GeoClipMapLOD();

        void renderLOD(Camera* _camera, Shader* _shader, Transform* _transform);

    private:
        void setupLevels(const unsigned int _levels, HeightMap* _heightMap, const float _maxHeight);

        std::vector<level_uptr> levels_;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_GEOCLIPMAPS_GEOCLIPMAPLOD_H_
