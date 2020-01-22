#include "collisionplane.h"

namespace NAGE
{
    CollisionPlane::CollisionPlane()
    {

    }

    float CollisionPlane::a() const
    {
        return mA;
    }

    float CollisionPlane::b() const
    {
        return mB;
    }

    float CollisionPlane::c() const
    {
        return mC;
    }

    float CollisionPlane::d() const
    {
        return mD;
    }

    float CollisionPlane::distance() const
    {
        return mD;
    }

    Vector4f CollisionPlane::vector4() const
    {
        return Vector4f(mA, mB, mC, mD);
    }

    Vector3f CollisionPlane::vector3() const
    {
        return Vector3f(mA, mB, mC);
    }

    void CollisionPlane::setA(float _a)
    {
        mA = _a;
    }

    void CollisionPlane::setB(float _b)
    {
        mB = _b;
    }

    void CollisionPlane::setC(float _c)
    {
        mC = _c;
    }

    void CollisionPlane::setD(float _d)
    {
        mD = _d;
    }

    void CollisionPlane::setVector(const Vector4f _vector)
    {
        mA = _vector.x();
        mB = _vector.y();
        mC = _vector.z();
        mD = _vector.w();
    }

    float CollisionPlane::dotCoord(float _x, float _y, float _z)
    {
        return mA * _x + mB * _y + mC * _z + mD;
    }

    float CollisionPlane::dotCoord(const Vector3f _point)
    {
        return dotCoord(_point.x(), _point.y(), _point.z());
    }

    void CollisionPlane::normalize()
    {
        float length = std::sqrt(mA * mA + mB * mB + mC * mC);

        mA /= length;
        mB /= length;
        mC /= length;
        mD /= length;
    }
}
