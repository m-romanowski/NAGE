#include "cdlodquadtree.h"

namespace mr::nage
{
    CDLODQuadTree::CDLODQuadTree(CDLODQuadTree* _parent, int _x, int _z, unsigned _lodLevel, int _dimension,
        HeightMap* _heightMap, NodeType _type)
        : CDLODNode(_x, _z, _lodLevel, _dimension),
          parent_(_parent),
          nodeType_(_type),
          heightmap_(_heightMap)
    {
        // Are we in leaf node?
        if(_lodLevel == 0)
        {
            minY_ = _heightMap->minValueFromArea(_x, _z, _dimension, _dimension);
            maxY_ = _heightMap->maxValueFromArea(_x, _z, _dimension, _dimension);
        }
        // Create new four node childs.
        else
        {
            int halfDimension = _dimension / 2;

            // Append four children.
            children_.push_back(new CDLODQuadTree(this, _x, _z, _lodLevel - 1, halfDimension,
                _heightMap, NodeType::TopLeft)); // Top-left
            children_.push_back(new CDLODQuadTree(this, _x + halfDimension, _z, _lodLevel - 1, halfDimension,
                _heightMap, NodeType::TopRight)); // Top-right
            children_.push_back(new CDLODQuadTree(this, _x, _z + halfDimension, _lodLevel - 1, halfDimension,
                _heightMap, NodeType::BottomLeft)); // Bottom-left
            children_.push_back(new CDLODQuadTree(this, _x + halfDimension, _z + halfDimension, _lodLevel - 1,
                halfDimension, _heightMap, NodeType::BottomRight)); // Bottom-right

            maxY_ = std::max(
                std::max(children_[TopLeft]->maxY_, children_[TopRight]->maxY_),
                std::max(children_[BottomLeft]->maxY_, children_[BottomRight]->maxY_)
            );

            minY_ = std::min(
                std::max(children_[TopLeft]->minY_, children_[TopRight]->minY_),
                std::max(children_[BottomLeft]->minY_, children_[BottomRight]->minY_)
            );
        }

        // Initialize node bounding box.
        nodeBoundingBox_.setMin(Vector3f(_x, minY_, _z));
        nodeBoundingBox_.setMax(Vector3f(_x + _dimension, maxY_, _z + _dimension));
    }

    CDLODQuadTree::~CDLODQuadTree()
    {
        for(auto& child : children_)
            delete child;

        delete parent_;
    }

    CDLODQuadTree* CDLODQuadTree::parent()
    {
        return parent_;
    }

    CDLODQuadTree* CDLODQuadTree::child(NodeType _type)
    {
        if(children_.size() == 0)
            return nullptr;

        return children_[_type];
    }

    std::vector<CDLODQuadTree*> CDLODQuadTree::children() const
    {
        return children_;
    }

    HeightMap* CDLODQuadTree::heightMap()
    {
        return heightmap_;
    }

    AABB& CDLODQuadTree::boundingBox()
    {
        return nodeBoundingBox_;
    }

    bool CDLODQuadTree::isRoot() const
    {
        if(nodeType_ == NodeType::Root)
            return true;

        return false;
    }

    bool CDLODQuadTree::isLeaf() const
    {
        if(children_.empty())
            return true;

        return false;
    }

    CDLODQuadTree::NodeType CDLODQuadTree::type() const
    {
        return nodeType_;
    }

    bool CDLODQuadTree::LODSelect(int* _ranges, int _lodLevel, FrustumCulling* _frustum, const Vector3f& _cameraPosition,
        std::vector<CDLODSelectedNode*>& _selectedNodes)
    {
        // False: our parent handles area.
        if(!nodeBoundingBox_.intersect(_cameraPosition, _ranges[_lodLevel]))
            return false;

        // True: this node was correctly handled.
        /*if(!_frustum->isAABBInside(nodeBoundingBox_))
            return true;*/

        // If its a root node.
        if(_lodLevel == 0)
        {
            // Add whole node to selection list.
            _selectedNodes.push_back(new CDLODSelectedNode(x_, z_, lodLevel_, dimension_, _ranges[_lodLevel],
                true, true, true, true));

            return true;
        }
        // Find selected nodes in leafs.
        else
        {
            if(!nodeBoundingBox_.intersect(_cameraPosition, _ranges[_lodLevel - 1]))
            {
                // Add while node to selection list.
                _selectedNodes.push_back(new CDLODSelectedNode(x_, z_, lodLevel_, dimension_, _ranges[_lodLevel],
                    true, true, true, true));
            }
            else
            {
                bool topLeftChild = true;
                bool topRightChild = true;
                bool bottomLeftChild = true;
                bool bottomRightChild = true;

                // We cover more detailed (child) levels.
                for(auto& child : children_)
                {
                    if(!child->LODSelect(_ranges, _lodLevel - 1, _frustum, _cameraPosition, _selectedNodes))
                    {
                        if(child->nodeType_ == NodeType::TopLeft) topLeftChild = false;
                        if(child->nodeType_ == NodeType::TopRight) topRightChild = false;
                        if(child->nodeType_ == NodeType::BottomLeft) bottomLeftChild = false;
                        if(child->nodeType_ == NodeType::BottomRight) bottomRightChild = false;
                    }
                }

                // Add part of of parent node area to selected list if child node is out of range.
                _selectedNodes.push_back(new CDLODSelectedNode(x_, z_, lodLevel_, dimension_, _ranges[_lodLevel],
                    topLeftChild, topRightChild, bottomLeftChild, bottomRightChild));
            }

            return true;
        }
    }
}
