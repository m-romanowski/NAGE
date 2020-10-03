#include "frustumculling.h"

namespace mr::nage
{
    FrustumCulling::FrustumCulling(bool _normalizePlanes)
        : normalizePlanes_(_normalizePlanes)
    {

    }

    void FrustumCulling::update(const Matrix4f& _mvp)
    {
        // Left
        planes_[0].setA(_mvp(4, 1) + _mvp(1, 1));
        planes_[0].setB(_mvp(4, 2) + _mvp(1, 2));
        planes_[0].setC(_mvp(4, 3) + _mvp(1, 3));
        planes_[0].setD(_mvp(4, 4) + _mvp(1, 4));

        // Right
        planes_[1].setA(_mvp(4, 1) - _mvp(1, 1));
        planes_[1].setB(_mvp(4, 2) - _mvp(1, 2));
        planes_[1].setC(_mvp(4, 3) - _mvp(1, 3));
        planes_[1].setD(_mvp(4, 4) - _mvp(1, 4));

        // Top
        planes_[2].setA(_mvp(4, 1) - _mvp(2, 1));
        planes_[2].setB(_mvp(4, 2) - _mvp(2, 2));
        planes_[2].setC(_mvp(4, 3) - _mvp(2, 3));
        planes_[2].setD(_mvp(4, 4) - _mvp(2, 4));

        // Bottom
        planes_[3].setA(_mvp(4, 1) + _mvp(2, 1));
        planes_[3].setB(_mvp(4, 2) + _mvp(2, 2));
        planes_[3].setC(_mvp(4, 3) + _mvp(2, 3));
        planes_[3].setD(_mvp(4, 4) + _mvp(2, 4));

        // Near
        planes_[4].setA(_mvp(4, 1) + _mvp(3, 1));
        planes_[4].setB(_mvp(4, 2) + _mvp(3, 2));
        planes_[4].setC(_mvp(4, 3) + _mvp(3, 3));
        planes_[4].setD(_mvp(4, 4) + _mvp(3, 4));

        // Far
        planes_[5].setA(_mvp(4, 1) - _mvp(3, 1));
        planes_[5].setB(_mvp(4, 2) - _mvp(3, 2));
        planes_[5].setC(_mvp(4, 3) - _mvp(3, 3));
        planes_[5].setD(_mvp(4, 4) - _mvp(3, 4));

        if(normalizePlanes_)
        {
            planes_[0].normalize();
            planes_[1].normalize();
            planes_[2].normalize();
            planes_[3].normalize();
            planes_[4].normalize();
            planes_[5].normalize();
        }
    }

    bool FrustumCulling::isPointInside(float _x, float _y, float _z)
    {
        for(auto& plane : planes_)
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
        for(auto& plane : planes_)
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
        for(auto& plane : planes_)
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

        for(auto& plane : planes_)
        {
            float d = Vector3f::dot(center, plane.vector3());
            float r = Vector3f::dot(extent, Vector3f::abs(plane.vector3()));

            if(d + r < -plane.distance())
                return false;
        }

        return true;
    }
}
