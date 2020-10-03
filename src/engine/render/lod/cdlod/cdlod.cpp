#include "cdlod.h"

namespace mr::nage
{
    CDLOD::CDLOD(CDLODSettings _settings)
        : cdlodSettings_(_settings)
    {

    }

    CDLOD::~CDLOD()
    {
        // Clear data.
        clearTreeNodes();
        clearSelectedNodes();
        delete[] cdlodRanges_;
    }

    int* CDLOD::ranges() const
    {
        return cdlodRanges_;
    }

    CDLODSettings CDLOD::settings() const
    {
        return cdlodSettings_;
    }

    std::vector<std::vector<CDLODQuadTree*>> CDLOD::treeNodes() const
    {
        return treeNodes_;
    }

    std::vector<CDLODSelectedNode*> CDLOD::selectedNodes() const
    {
        return selectedNodes_;
    }

    void CDLOD::setSettings(CDLODSettings _settings)
    {
        cdlodSettings_ = _settings;
    }

    void CDLOD::createQuadTree(HeightMap* _heightmap, int _lodLevel)
    {
        assert(_lodLevel <= cdlodSettings_.maxLODLevel_);

        int rootNodeSize = cdlodSettings_.leafNodeSize_ * std::pow(2, _lodLevel);
        int width = _heightmap->width();
        int height = _heightmap->height();

        cdlodRanges_ = new int[_lodLevel];
        for(int i = 1; i <= _lodLevel; i++)
            cdlodRanges_[i] = (1 << i); // 2 ^ i

        treeNodes_.resize(width / rootNodeSize);
        for(int i = 0; i < width / rootNodeSize; i++)
        {
            treeNodes_[i].resize(height / rootNodeSize);
            for(int j = 0; j < width / rootNodeSize; j++)
            {
                treeNodes_[i][j] = new CDLODQuadTree(nullptr, i * rootNodeSize, j * rootNodeSize, _lodLevel,
                    rootNodeSize, _heightmap, CDLODQuadTree::NodeType::Root);
            }
        }
    }

    void CDLOD::createSelectedList(int _rootLodLevel, FrustumCulling* _frustum, const Vector3f& _cameraPosition)
    {
        // For each all tree nodes.
        for(unsigned int i = 0; i < treeNodes_.size(); i++)
        {
            for(unsigned int j = 0; j < treeNodes_[0].size(); j++)
                treeNodes_[i][j]->LODSelect(cdlodRanges_, _rootLodLevel, _frustum, _cameraPosition, selectedNodes_);
        }
    }

    void CDLOD::clearTreeNodes()
    {
        for(unsigned int i = 0; i < treeNodes_.size(); i++)
        {
            for(unsigned int j = 0; j < treeNodes_[i].size(); j++)
                delete treeNodes_[i][j];
        }
    }

    void CDLOD::clearSelectedNodes()
    {
        selectedNodes_.clear();
    }
}
