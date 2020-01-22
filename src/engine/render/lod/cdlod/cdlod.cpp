#include "cdlod.h"

namespace NAGE
{
    CDLOD::CDLOD(CDLODSettings _settings)
        : mCDLODSettings(_settings)
    {

    }

    CDLOD::~CDLOD()
    {
        // Clear data.
        clearTreeNodes();
        clearSelectedNodes();
        delete[] mCDLODRanges;
    }

    int* CDLOD::ranges() const
    {
        return mCDLODRanges;
    }

    CDLODSettings CDLOD::settings() const
    {
        return mCDLODSettings;
    }

    std::vector<std::vector<CDLODQuadTree*>> CDLOD::treeNodes() const
    {
        return mTreeNodes;
    }

    std::vector<CDLODSelectedNode*> CDLOD::selectedNodes() const
    {
        return mSelectedNodes;
    }

    void CDLOD::setSettings(CDLODSettings _settings)
    {
        mCDLODSettings = _settings;
    }

    void CDLOD::createQuadTree(HeightMap* _heightmap, int _lodLevel)
    {
        assert(_lodLevel <= mCDLODSettings.maxLODLevel);

        int rootNodeSize = mCDLODSettings.leafNodeSize * std::pow(2, _lodLevel);
        int width = _heightmap->width();
        int height = _heightmap->height();

        mCDLODRanges = new int[_lodLevel];
        for(int i = 1; i <= _lodLevel; i++)
            mCDLODRanges[i] = (1 << i); // 2 ^ i

        mTreeNodes.resize(width / rootNodeSize);
        for(int i = 0; i < width / rootNodeSize; i++)
        {
            mTreeNodes[i].resize(height / rootNodeSize);
            for(int j = 0; j < width / rootNodeSize; j++)
            {
                mTreeNodes[i][j] = new CDLODQuadTree(nullptr, i * rootNodeSize, j * rootNodeSize, _lodLevel,
                    rootNodeSize, _heightmap, CDLODQuadTree::NodeType::Root);
            }
        }
    }

    void CDLOD::createSelectedList(int _rootLodLevel, FrustumCulling* _frustum, const Vector3f& _cameraPosition)
    {
        // For each all tree nodes.
        for(unsigned int i = 0; i < mTreeNodes.size(); i++)
        {
            for(unsigned int j = 0; j < mTreeNodes[0].size(); j++)
            {
                mTreeNodes[i][j]->LODSelect(mCDLODRanges, _rootLodLevel, _frustum, _cameraPosition, mSelectedNodes);
            }
        }
    }

    void CDLOD::clearTreeNodes()
    {
        for(unsigned int i = 0; i < mTreeNodes.size(); i++)
        {
            for(unsigned int j = 0; j < mTreeNodes[i].size(); j++)
            {
                delete mTreeNodes[i][j];
            }
        }
    }

    void CDLOD::clearSelectedNodes()
    {
        mSelectedNodes.clear();
    }
}
