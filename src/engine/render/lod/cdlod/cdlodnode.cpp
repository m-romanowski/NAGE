#include "cdlodnode.h"

namespace NAGE
{
    CDLODNode::CDLODNode(int _x, int _z, unsigned int _lodLevel, int _dimension)
        : mX(_x),
          mZ(_z),
          mDimension(_dimension),
          mLODLevel(_lodLevel)
    {

    }

    int CDLODNode::x() const
    {
        return mX;
    }

    int CDLODNode::z() const
    {
        return mZ;
    }

    int CDLODNode::minY() const
    {
        return mMinY;
    }

    int CDLODNode::maxY() const
    {
        return mMaxY;
    }

    int CDLODNode::dimension() const
    {
        return mDimension;
    }

    unsigned int CDLODNode::lodLevel() const
    {
        return mLODLevel;
    }
}
