#ifndef NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSETTINGS_H_
#define NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSETTINGS_H_

#define DEFAULT_CDLOD_MAX_LOD_LEVEL 16
#define DEFAULT_CDLOD_LEAF_NODE_SIZE 1 // 2 ^ n
#define DEFAULT_CDLOD_GRID_RESOLUTION 32 // 2 ^ n
#define DEFAULT_CDLOD_GRID_MESHES_COUNT 7

#include <cassert>

namespace NAGE
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
            maxLODLevel = DEFAULT_CDLOD_MAX_LOD_LEVEL;
            leafNodeSize = DEFAULT_CDLOD_LEAF_NODE_SIZE;
            gridResolution = DEFAULT_CDLOD_GRID_RESOLUTION;
            gridMeshesCount = DEFAULT_CDLOD_GRID_MESHES_COUNT;
            morphStartValue = 0.0f;
            morphStopValue = 0.25f;
        }

        // See paper: <= 128
        int dimension()
        {
            assert(leafNodeSize * gridResolution <= 128);
            return leafNodeSize * gridResolution;
        }

        // CDLOD settings
        int maxLODLevel; // Max lod level depth.
        int leafNodeSize; // Leaf node size
        int gridResolution; // Grid resolution.
        int gridMeshesCount; // Grid meshes count.
        float morphStartValue, morphStopValue; // Morph start and end value.
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSETTINGS_H_
