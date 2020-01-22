#ifndef NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSELECTEDNODE_H_
#define NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSELECTEDNODE_H_

#include "cdlodnode.h"

namespace NAGE
{
    class CDLODSelectedNode : public CDLODNode
    {
    public:
        CDLODSelectedNode(int _x, int _z, unsigned int _lodLevel, int _dimension, int _range,
            bool _topLeft, bool _topRight, bool _bottomLeft, bool _bottomRight);

        // Getters
        int range() const;
        bool topLeft() const;
        bool topRight() const;
        bool bottomLeft() const;
        bool bottomRight() const;

    private:
        int mRange;

        // Render some child quads (or all of them).
        bool mTopLeft;
        bool mTopRight;
        bool mBottomLeft;
        bool mBottomRight;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODSELECTEDNODE_H_
