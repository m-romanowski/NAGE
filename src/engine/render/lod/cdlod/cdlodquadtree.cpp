#include "cdlodquadtree.h"

namespace NAGE
{
    CDLODQuadTree::CDLODQuadTree(CDLODQuadTree* _parent, int _x, int _z, unsigned _lodLevel, int _dimension,
        HeightMap* _heightMap, NodeType _type)
        : CDLODNode(_x, _z, _lodLevel, _dimension),
          mParent(_parent),
          mNodeType(_type),
          mHeightmap(_heightMap)
    {
        // Are we in leaf node?
        if(_lodLevel == 0)
        {
            mMinY = _heightMap->minValueFromArea(_x, _z, _dimension, _dimension);
            mMaxY = _heightMap->maxValueFromArea(_x, _z, _dimension, _dimension);
        }
        // Create new four node childs.
        else
        {
            int halfDimension = _dimension / 2;

            // Append four children.
            mChildren.push_back(new CDLODQuadTree(this, _x, _z, _lodLevel - 1, halfDimension,
                _heightMap, NodeType::TopLeft)); // Top-left
            mChildren.push_back(new CDLODQuadTree(this, _x + halfDimension, _z, _lodLevel - 1, halfDimension,
                _heightMap, NodeType::TopRight)); // Top-right
            mChildren.push_back(new CDLODQuadTree(this, _x, _z + halfDimension, _lodLevel - 1, halfDimension,
                _heightMap, NodeType::BottomLeft)); // Bottom-left
            mChildren.push_back(new CDLODQuadTree(this, _x + halfDimension, _z + halfDimension, _lodLevel - 1,
                halfDimension, _heightMap, NodeType::BottomRight)); // Bottom-right

            mMaxY = std::max(
                std::max(mChildren[TopLeft]->mMaxY, mChildren[TopRight]->mMaxY),
                std::max(mChildren[BottomLeft]->mMaxY, mChildren[BottomRight]->mMaxY)
            );

            mMinY = std::min(
                std::max(mChildren[TopLeft]->mMinY, mChildren[TopRight]->mMinY),
                std::max(mChildren[BottomLeft]->mMinY, mChildren[BottomRight]->mMinY)
            );
        }

        // Initialize node bounding box.
        mNodeBoundingBox.setMin(Vector3f(_x, mMinY, _z));
        mNodeBoundingBox.setMax(Vector3f(_x + _dimension, mMaxY, _z + _dimension));
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

    CDLODQuadTree* CDLODQuadTree::child(NodeType _type)
    {
        if(mChildren.size() == 0)
            return nullptr;

        return mChildren[_type];
    }

    std::vector<CDLODQuadTree*> CDLODQuadTree::children() const
    {
        return mChildren;
    }

    HeightMap* CDLODQuadTree::heightMap()
    {
        return mHeightmap;
    }

    AABB& CDLODQuadTree::boundingBox()
    {
        return mNodeBoundingBox;
    }

    bool CDLODQuadTree::isRoot() const
    {
        if(mNodeType == NodeType::Root)
            return true;

        return false;
    }

    bool CDLODQuadTree::isLeaf() const
    {
        if(mChildren.empty())
            return true;

        return false;
    }

    CDLODQuadTree::NodeType CDLODQuadTree::type() const
    {
        return mNodeType;
    }

    bool CDLODQuadTree::LODSelect(int* _ranges, int _lodLevel, FrustumCulling* _frustum, const Vector3f& _cameraPosition,
        std::vector<CDLODSelectedNode*>& _selectedNodes)
    {
        // False: our parent handles area.
        if(!mNodeBoundingBox.intersect(_cameraPosition, _ranges[_lodLevel]))
            return false;

        // True: this node was correctly handled.
        /*if(!_frustum->isAABBInside(mNodeBoundingBox))
            return true;*/

        // If its a root node.
        if(_lodLevel == 0)
        {
            // Add whole node to selection list.
            _selectedNodes.push_back(new CDLODSelectedNode(mX, mZ, mLODLevel, mDimension, _ranges[_lodLevel],
                true, true, true, true));

            return true;
        }
        // Find selected nodes in leafs.
        else
        {
            if(!mNodeBoundingBox.intersect(_cameraPosition, _ranges[_lodLevel - 1]))
            {
                // Add while node to selection list.
                _selectedNodes.push_back(new CDLODSelectedNode(mX, mZ, mLODLevel, mDimension, _ranges[_lodLevel],
                    true, true, true, true));
            }
            else
            {
                bool topLeftChild = true;
                bool topRightChild = true;
                bool bottomLeftChild = true;
                bool bottomRightChild = true;

                // We cover more detailed (child) levels.
                for(auto& child : mChildren)
                {
                    if(!child->LODSelect(_ranges, _lodLevel - 1, _frustum, _cameraPosition, _selectedNodes))
                    {
                        if(child->mNodeType == NodeType::TopLeft) topLeftChild = false;
                        if(child->mNodeType == NodeType::TopRight) topRightChild = false;
                        if(child->mNodeType == NodeType::BottomLeft) bottomLeftChild = false;
                        if(child->mNodeType == NodeType::BottomRight) bottomRightChild = false;
                    }
                }

                // Add part of of parent node area to selected list if child node is out of range.
                _selectedNodes.push_back(new CDLODSelectedNode(mX, mZ, mLODLevel, mDimension, _ranges[_lodLevel],
                    topLeftChild, topRightChild, bottomLeftChild, bottomRightChild));
            }

            return true;
        }
    }
}
