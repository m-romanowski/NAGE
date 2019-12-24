#ifndef NAGE_ENGINE_RENDER_QUADTREE_H_
#define NAGE_ENGINE_RENDER_QUADTREE_H_

#include "quadtreenode.h"

#define MAX_TRAINGLES 10000

namespace NAGE
{
    class QuadTree
    {
    public:
        QuadTree();

        // Getters
        QuadTreeNode* parent();
        QuadTreeNode* northWest();
        QuadTreeNode* northEast();
        QuadTreeNode* southWest();
        QuadTreeNode* southEast();

    private:
        // Parent node.
        QuadTreeNode* mParent;

        // Children nodes.
        QuadTreeNode* mNorthWest;
        QuadTreeNode* mNorthEast;
        QuadTreeNode* mSouthWest;
        QuadTreeNode* mSouthEast;
    };
}

#endif // NAGE_ENGINE_RENDER_QUADTREE_H_
