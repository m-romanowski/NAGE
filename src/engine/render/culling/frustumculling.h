#ifndef NAGE_ENGINE_RENDER_CULLING_FRUSTUMCULLING_H_
#define NAGE_ENGINE_RENDER_CULLING_FRUSTUMCULLING_H_

#include "engine/render/collision/bs.h"
#include "engine/render/collision/aabb.h"
#include "engine/render/collision/collisionplane.h"
#include "engine/math/NAGEMath/nagemathmatrix.h"

#include <array>

namespace mr::nage
{
    /* Frustum culling
     *
     * Reference:
     * https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
     */
    class FrustumCulling
    {
    public:
        FrustumCulling(bool _normalizePlanes);

        bool intersect(const FrustumCulling _frustum);
        bool isPointInside(const Vector3f _point);
        bool isPointInside(float _x, float _y, float _z);
        bool isCubeInside(const Vector3f _point, float _radius);
        bool isCubeInside(float _x, float _y, float _z, float _radius);
        bool isSphereInside(float _x, float _y, float _z, float _radius);
        bool isSphereInside(const Vector3f _point, float _radius);
        bool isSphereInside(const BS _bs);
        bool isAABBInside(const Vector3f _min, const Vector3f _max);
        bool isAABBInside(const AABB _box);

        void update(const Matrix4f& _mvp);

    private:
        std::array<CollisionPlane, 6> planes_; // left, right, top, bottom, near, far
        bool normalizePlanes_;
    };
}

#endif // NAGE_ENGINE_RENDER_CULLING_FRUSTUMCULLING_H_
