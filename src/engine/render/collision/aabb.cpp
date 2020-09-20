#include "bs.h"
#include "aabb.h"

namespace NAGE
{
    AABB::AABB()
    {

    }

    float AABB::minX() const
    {
        return minX_;
    }

    float AABB::maxX() const
    {
        return maxX_;
    }

    float AABB::minY() const
    {
        return minY_;
    }

    float AABB::maxY() const
    {
        return maxY_;
    }

    float AABB::minZ() const
    {
        return minZ_;
    }

    float AABB::maxZ() const
    {
        return maxZ_;
    }

    Vector3f AABB::min() const
    {
        return Vector3f(minX_, minY_, minZ_);
    }

    Vector3f AABB::max() const
    {
        return Vector3f(maxX_, maxY_, maxZ_);
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
        minX_ = _x;
    }

    void AABB::setMaxX(float _x)
    {
        maxX_ = _x;
    }

    void AABB::setMinY(float _y)
    {
        minY_ = _y;
    }

    void AABB::setMaxY(float _y)
    {
        maxY_ = _y;
    }

    void AABB::setMinZ(float _z)
    {
        minZ_ = _z;
    }

    void AABB::setMaxZ(float _z)
    {
        maxZ_ = _z;
    }

    void AABB::setX(float _minX, float _maxX)
    {
        minX_ = _minX;
        maxX_ = _maxX;
    }

    void AABB::setY(float _minY, float _maxY)
    {
        minY_ = _minY;
        maxY_ = _maxY;
    }

    void AABB::setZ(float _minZ, float _maxZ)
    {
        minZ_ = _minZ;
        maxZ_ = _maxZ;
    }

    void AABB::setMin(const Vector3f _min)
    {
        minX_ = _min.x();
        minY_ = _min.y();
        minZ_ = _min.z();
    }

    void AABB::setMax(const Vector3f _max)
    {
        maxX_ = _max.x();
        maxY_ = _max.y();
        maxZ_ = _max.z();
    }

    void AABB::setMinMax(const Vector3f _min, const Vector3f _max)
    {
        setMin(_min);
        setMax(_max);
    }

    bool AABB::intersect(const BS _bs)
    {
        float x = std::max(minX_, std::min(_bs.x(), maxX_));
        float y = std::max(minY_, std::min(_bs.y(), maxY_));
        float z = std::max(minZ_, std::min(_bs.z(), maxZ_));

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
        return (minX_ <= _box.maxX_ && maxX_ >= _box.minX_) &&
            (minY_ <= _box.maxY_ && maxY_ >= _box.minY_) &&
            (minZ_ <= _box.minZ_ && maxZ_ >= _box.minZ_);
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
        return (_point.x() >= minX_ && _point.x() <= maxX_) &&
            (_point.y() >= minY_ && _point.y() <= maxY_) &&
            (_point.z() >= minZ_ && _point.z() <= maxZ_);
    }

    bool AABB::isPointInside(float _x, float _y, float _z)
    {
        return isPointInside(Vector3f(_x, _y, _z));
    }
}
