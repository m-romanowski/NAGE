#include "cdlodselectednode.h"

namespace NAGE
{
    CDLODSelectedNode::CDLODSelectedNode(int _x, int _z, unsigned int _lodLevel, int _dimension, int _range,
        bool _topLeft, bool _topRight, bool _bottomLeft, bool _bottomRight)
        : CDLODNode(_x, _z, _lodLevel, _dimension),
          range_(_range),
          topLeft_(_topLeft),
          topRight_(_topRight),
          bottomLeft_(_bottomLeft),
          bottomRight_(_bottomRight)
    {

    }

    int CDLODSelectedNode::range() const
    {
        return range_;
    }

    bool CDLODSelectedNode::topLeft() const
    {
        return topLeft_;
    }

    bool CDLODSelectedNode::topRight() const
    {
        return topRight_;
    }

    bool CDLODSelectedNode::bottomLeft() const
    {
        return bottomLeft_;
    }

    bool CDLODSelectedNode::bottomRight() const
    {
        return bottomRight_;
    }
}
