#include "quadtree.h"

namespace NAGE
{
    QuadTree::QuadTree()
    {

    }

    QuadTreeNode* QuadTree::parent()
    {
        return mParent;
    }

    QuadTreeNode* QuadTree::northWest()
    {
        return mNorthWest;
    }

    QuadTreeNode* QuadTree::northEast()
    {
        return mNorthEast;
    }

    QuadTreeNode* QuadTree::southWest()
    {
        return mSouthWest;
    }

    QuadTreeNode* QuadTree::southEast()
    {
        return mSouthEast;
    }
}
