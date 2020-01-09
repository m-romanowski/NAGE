#ifndef NAGE_ENGINE_RENDER_LOD_QUADTREE_H_
#define NAGE_ENGINE_RENDER_LOD_QUADTREE_H_

#include "engine/render/colision/aabb.h"
#include "engine/render/culling/frustumculling.h"
#include "engine/world/terrain/heightmap.h"

#include <vector>

/* https://github.com/fstrugar/CDLOD/blob/master/cdlod_paper_latest.pdf
 */
namespace NAGE
{
    class CDLODQuadTree
    {
    public:
        CDLODQuadTree(CDLODQuadTree* _parent, int _x, int _z, unsigned int _lodLevel, int _dimension, HeightMap* _heightMap);
        ~CDLODQuadTree();

        enum Child
        {
            TopLeft,
            TopRight,
            BottomLeft,
            BottomRight
        };

        // Getters
        CDLODQuadTree* parent();
        CDLODQuadTree* child(Child _type);
        std::vector<CDLODQuadTree*> children() const;
        bool isRoot() const;
        bool isLeaf() const;
        unsigned int lodLevel() const;
        int x() const;
        int z() const;
        int minY() const;
        int maxY() const;
        int dimension() const;
        HeightMap* heightMap();

        /* Begining from the mLodLevel and going to 0 (the heighest detailed level).

           https://github.com/fstrugar/CDLOD/blob/master/cdlod_paper_latest.pdf (p. 5 pseudocode).

           @param { int* } _ranges - array ...
           @param { int } _lodLeve - current LOD level.
           @param { FustumCulling* } - for AABB and sphere check.
           @return { bool } - this node was selected.
         */
        bool LODSelect(int* _ranges, int _lodLevel, FrustumCulling* _culling); // TODO

    private:
        // Parent node.
        CDLODQuadTree* mParent;

        // Quadtree children.
        std::vector<CDLODQuadTree*> mChildren;

        unsigned int mLodLevel; // Lod level: 0 - root
        int mX, mZ; // Position Vector3(x, height, z)
        int mMinY, mMaxY; // Minimmum and maximum heightmap value.
        int mDimension;
        HeightMap* mHeightmap;
        AABB mNodeBoundingBox;
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_QUADTREE_H_
