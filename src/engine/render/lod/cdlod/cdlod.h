#ifndef NAGE_ENGINE_RENDER_LOD_CDLOD_H_
#define NAGE_ENGINE_RENDER_LOD_CDLOD_H_

#include "cdlodsettings.h"
#include "cdlodquadtree.h"
#include "cdlodselectednode.h"

#include <vector>

namespace NAGE
{
    class CDLOD
    {
    public:
        CDLOD(CDLODSettings _settings = CDLODSettings());
        ~CDLOD();

        // Getters
        int* ranges() const;
        CDLODSettings settings() const;
        std::vector<std::vector<CDLODQuadTree*>> treeNodes() const;
        std::vector<CDLODSelectedNode*> selectedNodes() const;

        // Setters
        void setSettings(CDLODSettings _settings);

        void createQuadTree(HeightMap* _heightmap, int _rootLodLevel);
        void createSelectedList(int _rootLodLevel, FrustumCulling* _frustum, const Vector3f& _cameraPosition);
        void clearTreeNodes();
        void clearSelectedNodes();

    private:
        int* mCDLODRanges; // LOD ranges.
        CDLODSettings mCDLODSettings; // CDLOD Settings.
        std::vector<std::vector<CDLODQuadTree*>> mTreeNodes; // All tree nodes.
        std::vector<CDLODSelectedNode*> mSelectedNodes; // QuadTree nodes to render.
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLOD_H_
