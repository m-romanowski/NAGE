#ifndef QUADTREENODE_H
#define QUADTREENODE_H

namespace NAGE
{
    class QuadTreeNode
    {
    public:
        QuadTreeNode();

    private:
        // Node parent
        QuadTreeNode* parent;

        // Node children - north west, north east, south west, south east.
        QuadTreeNode* mNW;
        QuadTreeNode* mNE;
        QuadTreeNode* mSW;
        QuadTreeNode* mSE;
    };
}

#endif // QUADTREENODE_H
