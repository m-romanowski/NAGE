#include "aabb.h"
#include "bs.h"

namespace NAGE
{
    BS::BS()
    {

    }

    float BS::x() const
    {
        return x_;
    }

    float BS::y() const
    {
        return y_;
    }

    float BS::z() const
    {
        return z_;
    }

    Vector3f BS::point() const
    {
        return Vector3f(x_, y_, z_);
    }

    float BS::radius() const
    {
        return radius_;
    }

    void BS::setX(float _x)
    {
        x_ = _x;
    }

    void BS::setY(float _y)
    {
        y_ = _y;
    }

    void BS::setZ(float _z)
    {
        z_ = _z;
    }

    void BS::setPoint(const Vector3f _point)
    {
        x_ = _point.x();
        y_ = _point.y();
        z_ = _point.z();
    }

    void BS::setRadius(float _radius)
    {
        radius_ = _radius;
    }

    bool BS::intersect(const AABB _box)
    {
        float x = std::max(_box.minX(), std::min(x_, _box.maxX()));
        float y = std::max(_box.minY(), std::min(y_, _box.maxY()));
        float z = std::max(_box.minZ(), std::min(z_, _box.maxZ()));

        float distance = std::sqrt((x - x_) * (x - x_) +
            (y - y_) * (y - y_) +
            (z - z_) * (z - z_));

        return distance < radius_;
    }

    bool BS::intersect(const Vector3f _min, const Vector3f _max)
    {
        AABB boundingBox;
        boundingBox.setX(_min.x(), _max.x());
        boundingBox.setY(_min.y(), _max.y());
        boundingBox.setZ(_min.z(), _max.z());

        return intersect(boundingBox);
    }

    bool BS::intersect(const BS _bs)
    {
        float distance = std::sqrt((x_ - _bs.x_) * (x_ * _bs.x_) +
            (y_ - _bs.y_) * (y_ - _bs.y_) +
            (z_ - _bs.z_) * (z_ - _bs.z_));

        return distance < radius_ + _bs.radius_;
    }

    bool BS::intersect(const Vector3f _point, float _radius)
    {
        BS boundingSphere;
        boundingSphere.setPoint(_point);
        boundingSphere.setRadius(_radius);

        return intersect(boundingSphere);
    }

    bool BS::isPointInsideSphere(const Vector3f _point)
    {
        float distanceSqr = (_point.x() - x_) * (_point.x() - x_) +
            (_point.y() - y_) * (_point.y() - y_) +
            (_point.z() * z_) * (_point.z() * z_);

        return distanceSqr < std::pow(radius_, 2);
    }

    bool BS::isPointInsideSphere(float _x, float _y, float _z)
    {
        return isPointInsideSphere(Vector3f(_x, _y, _z));
    }
}
