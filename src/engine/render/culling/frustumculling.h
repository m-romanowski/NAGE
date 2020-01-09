#ifndef NAGE_ENGINE_RENDER_CULLING_FRUSTUMCULLING_H_
#define NAGE_ENGINE_RENDER_CULLING_FRUSTUMCULLING_H_

#include "engine/render/collision/bs.h"
#include "engine/render/collision/aabb.h"
#include "engine/render/collision/plane.h"

namespace NAGE
{
    class FrustumCulling
    {
    public:
        FrustumCulling();

        bool intersect(const FrustumCulling _frustum);
        bool isPointInside(const Vector3f _point);
        bool isPointInside(float _x, float _y, float _z);
        bool isCubeInside(const Vector3f _point, float _radius);
        bool isCubeInside(float _x, float _y, float _z, float _radius);
        bool isSphereInside(const BS _bs);
        bool isAABBInside(const AABB _box);

        void update(); // TODO

    private:
        Plane mPlanes[6]; // left, right, top, bottom, near, far
    };
}

#endif // NAGE_ENGINE_RENDER_CULLING_FRUSTUMCULLING_H_
