#ifndef NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODQUADTREE_H_
#define NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODQUADTREE_H_

#include "cdlodnode.h"
#include "cdlodselectednode.h"
#include "engine/render/collision/aabb.h"
#include "engine/render/culling/frustumculling.h"
#include "engine/generators/heightmap.h"

#include <vector>

/**
 * Original paper: https://github.com/fstrugar/CDLOD/blob/master/cdlod_paper_latest.pdf
 */
namespace NAGE
{
    class CDLODQuadTree : public CDLODNode
    {
    public:
        enum NodeType
        {
            TopLeft,
            TopRight,
            BottomLeft,
            BottomRight,
            Root = -1
        };

        CDLODQuadTree(CDLODQuadTree* _parent, int _x, int _z, unsigned int _lodLevel, int _dimension,
            HeightMap* _heightMap, NodeType _type);
        ~CDLODQuadTree();

        // Getters
        CDLODQuadTree* parent();
        CDLODQuadTree* child(NodeType _type);
        std::vector<CDLODQuadTree*> children() const;
        HeightMap* heightMap();
        AABB& boundingBox();
        bool isLeaf() const;
        bool isRoot() const;
        NodeType type() const;

        /* Begining from the mLodLevel and going to 0 (the heighest detailed level).
         *
         * Reference:
         * https://github.com/fstrugar/CDLOD/blob/master/cdlod_paper_latest.pdf (see page 5 - pseudocode).
         */
        bool LODSelect(int* _ranges, int _lodLevel, FrustumCulling* _culling, const Vector3f& _cameraPosition,
            std::vector<CDLODSelectedNode*>& _selectedNodes);

    private:
        // Parent node.
        CDLODQuadTree* mParent;

        // Node type
        NodeType mNodeType;

        std::vector<CDLODQuadTree*> mChildren; // Quadtree children (4)
        HeightMap* mHeightmap; // LOD heightmap.
        AABB mNodeBoundingBox; // Node axis aligned bounding box
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODQUADTREE_H_
