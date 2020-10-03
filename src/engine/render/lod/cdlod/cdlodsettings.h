#ifndef NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSETTINGS_H_
#define NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSETTINGS_H_

#define DEFAULT_CDLOD_MAX_LOD_LEVEL 16
#define DEFAULT_CDLOD_LEAF_NODE_SIZE 1 // 2 ^ n
#define DEFAULT_CDLOD_GRID_RESOLUTION 32 // 2 ^ n
#define DEFAULT_CDLOD_GRID_MESHES_COUNT 7

#include <cassert>

namespace mr::nage
{
    class CDLODSettings
    {
    public:
        CDLODSettings()
        {
            setDefaultSettings();
        }

        void setDefaultSettings()
        {
            maxLODLevel_ = DEFAULT_CDLOD_MAX_LOD_LEVEL;
            leafNodeSize_ = DEFAULT_CDLOD_LEAF_NODE_SIZE;
            gridResolution_ = DEFAULT_CDLOD_GRID_RESOLUTION;
            gridMeshesCount_ = DEFAULT_CDLOD_GRID_MESHES_COUNT;
            morphStartValue_ = 0.0f;
            morphEndValue_ = 0.25f;
        }

        // See paper: <= 128
        int dimension()
        {
            assert(leafNodeSize_ * gridResolution_ <= 128);
            return leafNodeSize_ * gridResolution_;
        }

        // CDLOD settings
        int maxLODLevel_; // Max lod level depth.
        int leafNodeSize_; // Leaf node size
        int gridResolution_; // Grid resolution.
        int gridMeshesCount_; // Grid meshes count.
        float morphStartValue_, morphEndValue_; // Morph start and end value.
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSETTINGS_H_
