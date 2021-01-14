#include "geoclipmaplod.h"

namespace mr::nage
{
    GeoClipMapLOD::GeoClipMapLOD(const unsigned int _levels, HeightMap* _heightMap, const float _maxHeight)
    {
        setupLevels(_levels, _heightMap, _maxHeight);
    }

    GeoClipMapLOD::~GeoClipMapLOD()
    {
        levels_.clear();
    }

    void GeoClipMapLOD::setupLevels(const unsigned int _levels, HeightMap* _heightMap, const float _maxHeight)
    {
        for(unsigned int i = _levels; i > 0; i--)
        {
            // TODO: confgurable grid size.
            level_uptr level = std::make_unique<GeoClipMapLevel>(255, i, _heightMap, _maxHeight);
            levels_.push_back(std::move(level));
        }

        for(unsigned int i = 0; i < levels_.size(); i++)
        {
            GeoClipMapLevel* parentLevel = nullptr;
            GeoClipMapLevel* childLevel = nullptr;

            if(i != levels_.size() - 1)
                parentLevel = levels_.at(i + 1).get();

            if(i > 0)
                childLevel = levels_.at(i - 1).get();

            levels_.at(i).get()->create(parentLevel, childLevel);
        }
    }

    void GeoClipMapLOD::renderLOD(Camera* _camera, Shader* _shader, Transform* _transform)
    {
        NAGE_UNUSED(_transform);

        // TODO: don't render invisible levels (bounding box line CDLOD).
        for(auto& level : levels_)
            level.get()->render(_camera, _shader);
    }
}
