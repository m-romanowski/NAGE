#ifndef NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODNODE_H_
#define NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODNODE_H_

namespace NAGE
{
    class CDLODNode
    {
    public:
        CDLODNode(int _x, int _z, unsigned int _lodLevel, int _dimension);

        // Getters
        int x() const;
        int z() const;
        int minY() const;
        int maxY() const;
        int dimension() const;
        unsigned int lodLevel() const;

    protected:
        int x_, z_; // Position Vector3(x, height, z)
        int minY_, maxY_; // Minimmum and maximum heightmap value.
        int dimension_; // Node dimension.
        unsigned int lodLevel_; // Lod level: 0 - root
    };
}

#endif // NAGE_ENGINE_RENDER_LOD_CDLOD_CDLODNODE_H_
