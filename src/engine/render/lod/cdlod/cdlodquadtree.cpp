#include "cdlodquadtree.h"

namespace NAGE
{
    CDLODQuadTree::CDLODQuadTree(CDLODQuadTree* _parent, int _x, int _z, unsigned _lodLevel, int _dimension, HeightMap* _heightMap)
        : mParent(_parent),
          mLodLevel(_lodLevel),
          mX(_x),
          mZ(_z),
          mDimension(_dimension),
          mHeightmap(_heightMap)
    {
        // Is leaf?
        if(_lodLevel == 0)
        {
            mParent = nullptr;
            mMinY = _heightMap->minValueFromArea(_x, _z, _dimension, _dimension);
            mMaxY = _heightMap->maxValueFromArea(_x, _z, _dimension, _dimension);
        }
        else
        {
            int halfDimension = _dimension / 2;

            // Append four children.
            mChildren.push_back(new CDLODQuadTree(this, _x, _z, _lodLevel - 1, halfDimension, _heightMap)); // Top-left
            mChildren.push_back(new CDLODQuadTree(this, _x + halfDimension, _z, _lodLevel - 1, halfDimension, _heightMap)); // Top-right
            mChildren.push_back(new CDLODQuadTree(this, _x, _z + halfDimension, _lodLevel - 1, halfDimension, _heightMap)); // Bottom-left
            mChildren.push_back(new CDLODQuadTree(this, _x + halfDimension, _z + halfDimension, _lodLevel - 1, halfDimension, _heightMap)); // Bottom-right

            mMaxY = std::max(
                std::max(mChildren[TopLeft]->mMaxY, mChildren[TopRight]->mMaxY),
                std::max(mChildren[BottomLeft]->mMaxY, mChildren[BottomRight]->mMaxY)
            );

            mMinY = std::min(
                std::max(mChildren[TopLeft]->mMinY, mChildren[TopRight]->mMinY),
                std::max(mChildren[BottomLeft]->mMinY, mChildren[BottomRight]->mMinY)
            );
        }
    }

    CDLODQuadTree::~CDLODQuadTree()
    {
        for(auto& child : mChildren)
            delete child;

        delete mParent;
    }

    CDLODQuadTree* CDLODQuadTree::parent()
    {
        return mParent;
    }

    CDLODQuadTree* CDLODQuadTree::child(Child _type)
    {
        if(mChildren.size() == 0)
            return nullptr;

        return mChildren[_type];
    }

    std::vector<CDLODQuadTree*> CDLODQuadTree::children() const
    {
        return mChildren;
    }

    bool CDLODQuadTree::isRoot() const
    {
        return false;
    }

    bool CDLODQuadTree::isLeaf() const
    {
        return false;
    }

    unsigned int CDLODQuadTree::lodLevel() const
    {
        return mLodLevel;
    }

    int CDLODQuadTree::x() const
    {
        return mX;
    }

    int CDLODQuadTree::z() const
    {
        return mZ;
    }

    int CDLODQuadTree::minY() const
    {
        return mMinY;
    }

    int CDLODQuadTree::maxY() const
    {
        return mMaxY;
    }

    int CDLODQuadTree::dimension() const
    {
        return mDimension;
    }

    bool CDLODQuadTree::LODSelect(int* _ranges, int _lodLevel, FrustumCulling* _culling)
    {

    }
}
