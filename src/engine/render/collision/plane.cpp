#include "plane.h"

namespace NAGE
{
    Plane::Plane()
    {

    }

    float Plane::a() const
    {
        return mA;
    }

    float Plane::b() const
    {
        return mB;
    }

    float Plane::c() const
    {
        return mC;
    }

    float Plane::d() const
    {
        return mD;
    }

    void Plane::setA(float _a)
    {
        mA = _a;
    }

    void Plane::setB(float _b)
    {
        mB = _b;
    }

    void Plane::setC(float _c)
    {
        mC = _c;
    }

    void Plane::setD(float _d)
    {
        mD = _d;
    }

    float Plane::dotCoord(float _x, float _y, float _z)
    {
        return mA * _x + mB * _y + mC * _z + mD;
    }

    float Plane::dotCoord(const Vector3f _point)
    {
        return dotCoord(_point.x(), _point.y(), _point.z());
    }

    void Plane::normalize()
    {

    }
}
