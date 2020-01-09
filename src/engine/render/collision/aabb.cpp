#include "bs.h"
#include "aabb.h"

namespace NAGE
{
    AABB::AABB()
    {

    }

    float AABB::minX() const
    {
        return mMinX;
    }

    float AABB::maxX() const
    {
        return mMaxX;
    }

    float AABB::minY() const
    {
        return mMinY;
    }

    float AABB::maxY() const
    {
        return mMaxY;
    }

    float AABB::minZ() const
    {
        return mMinZ;
    }

    float AABB::maxZ() const
    {
        return mMaxZ;
    }

    void AABB::setMinX(float _x)
    {
        mMinX = _x;
    }

    void AABB::setMaxX(float _x)
    {
        mMaxX = _x;
    }

    void AABB::setMinY(float _y)
    {
        mMinY = _y;
    }

    void AABB::setMaxY(float _y)
    {
        mMaxY = _y;
    }

    void AABB::setMinZ(float _z)
    {
        mMinZ = _z;
    }

    void AABB::setMaxZ(float _z)
    {
        mMaxZ = _z;
    }

    void AABB::setX(float _minX, float _maxX)
    {
        mMinX = _minX;
        mMaxX = _maxX;
    }

    void AABB::setY(float _minY, float _maxY)
    {
        mMinY = _minY;
        mMaxY = _maxY;
    }

    void AABB::setZ(float _minZ, float _maxZ)
    {
        mMinZ = _minZ;
        mMaxZ = _maxZ;
    }

    bool AABB::intersect(const BS _bs)
    {
        float x = std::max(mMinX, std::min(_bs.x(), mMaxX));
        float y = std::max(mMinY, std::min(_bs.y(), mMaxY));
        float z = std::max(mMinZ, std::min(_bs.z(), mMaxZ));

        float distance = std::sqrt((x - _bs.x()) * (x - _bs.x()) +
            (y - _bs.y()) * (y - _bs.y()) +
            (z - _bs.z()) * (z - _bs.z()));

        return distance < _bs.radius();
    }

    bool AABB::intersect(const AABB _box)
    {
        return (mMinX <= _box.mMaxX && mMaxX >= _box.mMinX) &&
               (mMinY <= _box.mMaxY && mMaxY >= _box.mMinY) &&
               (mMinZ <= _box.mMinZ && mMaxZ >= _box.mMinZ);
    }

    bool AABB::intersect(const AABB _boxA, const AABB _boxB)
    {
        return (_boxA.mMinX <= _boxB.mMaxX && _boxA.mMaxX >= _boxB.mMinX) &&
               (_boxA.mMinY <= _boxB.mMaxY && _boxA.mMaxY >= _boxB.mMinY) &&
               (_boxA.mMinZ <= _boxB.mMinZ && _boxA.mMaxZ >= _boxB.mMinZ);
    }

    bool AABB::isPointInside(const Vector3f _point)
    {
        return (_point.x() >= mMinX && _point.x() <= mMaxX) &&
               (_point.y() >= mMinY && _point.y() <= mMaxY) &&
               (_point.z() >= mMinZ && _point.z() <= mMaxZ);
    }

    bool AABB::isPointInside(const AABB _box, const Vector3f _point)
    {
        return (_point.x() >= _box.mMinX && _point.x() <= _box.mMaxX) &&
               (_point.y() >= _box.mMinY && _point.y() <= _box.mMaxY) &&
               (_point.z() >= _box.mMinZ && _point.z() <= _box.mMaxZ);
    }
}
