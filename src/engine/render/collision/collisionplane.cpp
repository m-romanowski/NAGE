#include "collisionplane.h"

namespace NAGE
{
    CollisionPlane::CollisionPlane()
    {

    }

    float CollisionPlane::a() const
    {
        return a_;
    }

    float CollisionPlane::b() const
    {
        return b_;
    }

    float CollisionPlane::c() const
    {
        return c_;
    }

    float CollisionPlane::d() const
    {
        return d_;
    }

    float CollisionPlane::distance() const
    {
        return d_;
    }

    Vector4f CollisionPlane::vector4() const
    {
        return Vector4f(a_, b_, c_, d_);
    }

    Vector3f CollisionPlane::vector3() const
    {
        return Vector3f(a_, b_, c_);
    }

    void CollisionPlane::setA(float _a)
    {
        a_ = _a;
    }

    void CollisionPlane::setB(float _b)
    {
        b_ = _b;
    }

    void CollisionPlane::setC(float _c)
    {
        c_ = _c;
    }

    void CollisionPlane::setD(float _d)
    {
        d_ = _d;
    }

    void CollisionPlane::setVector(const Vector4f _vector)
    {
        a_ = _vector.x();
        b_ = _vector.y();
        c_ = _vector.z();
        d_ = _vector.w();
    }

    float CollisionPlane::dotCoord(float _x, float _y, float _z)
    {
        return a_ * _x + b_ * _y + c_ * _z + d_;
    }

    float CollisionPlane::dotCoord(const Vector3f _point)
    {
        return dotCoord(_point.x(), _point.y(), _point.z());
    }

    void CollisionPlane::normalize()
    {
        float length = std::sqrt(a_ * a_ + b_ * b_ + c_ * c_);

        a_ /= length;
        b_ /= length;
        c_ /= length;
        d_ /= length;
    }
}
