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

    Vector3f AABB::min() const
    {
        return Vector3f(mMinX, mMinY, mMinZ);
    }

    Vector3f AABB::max() const
    {
        return Vector3f(mMaxX, mMaxY, mMaxZ);
    }

    Vector3f AABB::center() const
    {
        return 0.5f * (min() + max());
    }

    Vector3f AABB::extent() const
    {
        return max() - min();
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

    void AABB::setMin(const Vector3f _min)
    {
        mMinX = _min.x();
        mMinY = _min.y();
        mMinZ = _min.z();
    }

    void AABB::setMax(const Vector3f _max)
    {
        mMaxX = _max.x();
        mMaxY = _max.y();
        mMaxZ = _max.z();
    }

    void AABB::setMinMax(const Vector3f _min, const Vector3f _max)
    {
        setMin(_min);
        setMax(_max);
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

    bool AABB::intersect(const Vector3f _point, float _radius)
    {
        BS boundingSphere;
        boundingSphere.setPoint(_point);
        boundingSphere.setRadius(_radius);

        return intersect(boundingSphere);
    }

    bool AABB::intersect(const AABB _box)
    {
        return (mMinX <= _box.mMaxX && mMaxX >= _box.mMinX) &&
            (mMinY <= _box.mMaxY && mMaxY >= _box.mMinY) &&
            (mMinZ <= _box.mMinZ && mMaxZ >= _box.mMinZ);
    }

    bool AABB::intersect(const Vector3f _min, const Vector3f _max)
    {
        AABB boundingBox;
        boundingBox.setX(_min.x(), _max.x());
        boundingBox.setY(_min.y(), _max.y());
        boundingBox.setZ(_min.z(), _max.z());

        return intersect(boundingBox);
    }

    bool AABB::isPointInside(const Vector3f _point)
    {
        return (_point.x() >= mMinX && _point.x() <= mMaxX) &&
            (_point.y() >= mMinY && _point.y() <= mMaxY) &&
            (_point.z() >= mMinZ && _point.z() <= mMaxZ);
    }

    bool AABB::isPointInside(float _x, float _y, float _z)
    {
        return isPointInside(Vector3f(_x, _y, _z));
    }
}
