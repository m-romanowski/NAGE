#include "cdlodselectednode.h"

namespace NAGE
{
    CDLODSelectedNode::CDLODSelectedNode(int _x, int _z, unsigned int _lodLevel, int _dimension, int _range,
        bool _topLeft, bool _topRight, bool _bottomLeft, bool _bottomRight)
        : CDLODNode(_x, _z, _lodLevel, _dimension),
          mRange(_range),
          mTopLeft(_topLeft),
          mTopRight(_topRight),
          mBottomLeft(_bottomLeft),
          mBottomRight(_bottomRight)
    {

    }

    int CDLODSelectedNode::range() const
    {
        return mRange;
    }

    bool CDLODSelectedNode::topLeft() const
    {
        return mTopLeft;
    }

    bool CDLODSelectedNode::topRight() const
    {
        return mTopRight;
    }

    bool CDLODSelectedNode::bottomLeft() const
    {
        return mBottomLeft;
    }

    bool CDLODSelectedNode::bottomRight() const
    {
        return mBottomRight;
    }
}
