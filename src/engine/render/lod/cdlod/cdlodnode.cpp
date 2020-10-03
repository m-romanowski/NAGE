#include "cdlodnode.h"

namespace mr::nage
{
    CDLODNode::CDLODNode(int _x, int _z, unsigned int _lodLevel, int _dimension)
        : x_(_x),
          z_(_z),
          dimension_(_dimension),
          lodLevel_(_lodLevel)
    {

    }

    int CDLODNode::x() const
    {
        return x_;
    }

    int CDLODNode::z() const
    {
        return z_;
    }

    int CDLODNode::minY() const
    {
        return minY_;
    }

    int CDLODNode::maxY() const
    {
        return maxY_;
    }

    int CDLODNode::dimension() const
    {
        return dimension_;
    }

    unsigned int CDLODNode::lodLevel() const
    {
        return lodLevel_;
    }
}
