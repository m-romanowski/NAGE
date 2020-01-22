#include "frustumculling.h"

namespace NAGE
{
    FrustumCulling::FrustumCulling(bool _normalizePlanes)
        : mNormalizePlanes(_normalizePlanes)
    {

    }

    void FrustumCulling::update(const Matrix4f& _mvp)
    {
        // Left
        mPlanes[0].setA(_mvp(4, 1) + _mvp(1, 1));
        mPlanes[0].setB(_mvp(4, 2) + _mvp(1, 2));
        mPlanes[0].setC(_mvp(4, 3) + _mvp(1, 3));
        mPlanes[0].setD(_mvp(4, 4) + _mvp(1, 4));

        // Right
        mPlanes[1].setA(_mvp(4, 1) - _mvp(1, 1));
        mPlanes[1].setB(_mvp(4, 2) - _mvp(1, 2));
        mPlanes[1].setC(_mvp(4, 3) - _mvp(1, 3));
        mPlanes[1].setD(_mvp(4, 4) - _mvp(1, 4));

        // Top
        mPlanes[2].setA(_mvp(4, 1) - _mvp(2, 1));
        mPlanes[2].setB(_mvp(4, 2) - _mvp(2, 2));
        mPlanes[2].setC(_mvp(4, 3) - _mvp(2, 3));
        mPlanes[2].setD(_mvp(4, 4) - _mvp(2, 4));

        // Bottom
        mPlanes[3].setA(_mvp(4, 1) + _mvp(2, 1));
        mPlanes[3].setB(_mvp(4, 2) + _mvp(2, 2));
        mPlanes[3].setC(_mvp(4, 3) + _mvp(2, 3));
        mPlanes[3].setD(_mvp(4, 4) + _mvp(2, 4));

        // Near
        mPlanes[4].setA(_mvp(4, 1) + _mvp(3, 1));
        mPlanes[4].setB(_mvp(4, 2) + _mvp(3, 2));
        mPlanes[4].setC(_mvp(4, 3) + _mvp(3, 3));
        mPlanes[4].setD(_mvp(4, 4) + _mvp(3, 4));

        // Far
        mPlanes[5].setA(_mvp(4, 1) - _mvp(3, 1));
        mPlanes[5].setB(_mvp(4, 2) - _mvp(3, 2));
        mPlanes[5].setC(_mvp(4, 3) - _mvp(3, 3));
        mPlanes[5].setD(_mvp(4, 4) - _mvp(3, 4));

        if(mNormalizePlanes)
        {
            mPlanes[0].normalize();
            mPlanes[1].normalize();
            mPlanes[2].normalize();
            mPlanes[3].normalize();
            mPlanes[4].normalize();
            mPlanes[5].normalize();
        }
    }

    bool FrustumCulling::isPointInside(float _x, float _y, float _z)
    {
        for(auto& plane : mPlanes)
        {
            if(plane.dotCoord(_x, _y, _z) < 0.0f)
                return false;
        }

        return true;
    }

    bool FrustumCulling::isPointInside(const Vector3f _point)
    {
        return isPointInside(_point.x(), _point.y(), _point.z());
    }

    bool FrustumCulling::isCubeInside(float _x, float _y, float _z, float _radius)
    {
        for(auto& plane : mPlanes)
        {
            if(plane.dotCoord(_x - _radius, _y - _radius, _z - _radius) >= 0)
                continue;

            if(plane.dotCoord(_x + _radius, _y - _radius, _z - _radius) >= 0)
                continue;

            if(plane.dotCoord(_x - _radius, _y + _radius, _z - _radius) >= 0)
                continue;

            if(plane.dotCoord(_x + _radius, _y + _radius, _z - _radius) >= 0)
                continue;

            if(plane.dotCoord(_x - _radius, _y - _radius, _z + _radius) >= 0)
                continue;

            if(plane.dotCoord(_x + _radius, _y - _radius, _z + _radius) >= 0)
                continue;

            if(plane.dotCoord(_x - _radius, _y + _radius, _z + _radius) >= 0)
                continue;

            if(plane.dotCoord(_x + _radius, _y + _radius, _z + _radius) >= 0)
                continue;

            return false;
        }

        return true;
    }

    bool FrustumCulling::isCubeInside(const Vector3f _point, float _radius)
    {
        return isCubeInside(_point.x(), _point.y(), _point.z(), _radius);
    }

    bool FrustumCulling::isSphereInside(float _x, float _y, float _z, float _radius)
    {
        for(auto& plane : mPlanes)
        {
            if(plane.dotCoord(_x, _y, _z) < -_radius)
                return false;
        }

        return true;
    }

    bool FrustumCulling::isSphereInside(const Vector3f _point, float _radius)
    {
        return isSphereInside(_point.x(), _point.y(), _point.z(), _radius);
    }

    bool FrustumCulling::isSphereInside(const BS _bs)
    {
        return isSphereInside(_bs.x(), _bs.y(), _bs.z(), _bs.radius());
    }

    bool FrustumCulling::isAABBInside(const Vector3f _min, const Vector3f _max)
    {
        AABB boundingBox;
        boundingBox.setMin(_min);
        boundingBox.setMax(_max);

        return isAABBInside(boundingBox);
    }

    bool FrustumCulling::isAABBInside(const AABB _box)
    {
        Vector3f center = _box.center();
        Vector3f extent = _box.extent();

        for(auto& plane : mPlanes)
        {
            float d = Vector3f::dot(center, plane.vector3());
            float r = Vector3f::dot(extent, Vector3f::abs(plane.vector3()));

            if(d + r < -plane.distance())
                return false;
        }

        return true;
    }
}
