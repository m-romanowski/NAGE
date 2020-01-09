#include "aabb.h"
#include "bs.h"

namespace NAGE
{
    BS::BS()
    {

    }

    float BS::x() const
    {
        return mX;
    }

    float BS::y() const
    {
        return mY;
    }

    float BS::z() const
    {
        return mZ;
    }

    Vector3f BS::point() const
    {
        return Vector3f(mX, mY, mZ);
    }

    float BS::radius() const
    {
        return mRadius;
    }

    void BS::setX(float _x)
    {
        mX = _x;
    }

    void BS::setY(float _y)
    {
        mY = _y;
    }

    void BS::setZ(float _z)
    {
        mZ = _z;
    }

    void BS::setPoint(const Vector3f _point)
    {
        mX = _point.x();
        mY = _point.y();
        mZ = _point.z();
    }

    void BS::setRadius(float _radius)
    {
        mRadius = _radius;
    }

    bool BS::intersect(const AABB _box)
    {
        float x = std::max(_box.minX(), std::min(mX, _box.maxX()));
        float y = std::max(_box.minY(), std::min(mY, _box.maxY()));
        float z = std::max(_box.minZ(), std::min(mZ, _box.maxZ()));

        float distance = std::sqrt((x - mX) * (x - mX) +
            (y - mY) * (y - mY) +
            (z - mZ) * (z - mZ));

        return distance < mRadius;
    }

    bool BS::intersect(const BS _bs)
    {
        float distance = std::sqrt((mX - _bs.mX) * (mX * _bs.mX) +
            (mY - _bs.mY) * (mY - _bs.mY) +
            (mZ - _bs.mZ) * (mZ - _bs.mZ));

        return distance < mRadius + _bs.mRadius;
    }

    bool BS::intersect(const BS _bsA, const BS _bsB)
    {
        float distance = std::sqrt((_bsA.mX - _bsB.mX) * (_bsA.mX * _bsB.mX) +
            (_bsA.mY - _bsB.mY) * (_bsA.mY - _bsB.mY) +
            (_bsA.mZ - _bsB.mZ) * (_bsA.mZ - _bsB.mZ));

        return distance < _bsA.mRadius + _bsB.mRadius;
    }

    bool BS::isPointInsideSphere(const Vector3f _point)
    {
        float distanceSqr = (_point.x() - mX) * (_point.x() - mX) +
            (_point.y() - mY) * (_point.y() - mY) +
            (_point.z() * mZ) * (_point.z() * mZ);

        return distanceSqr < std::pow(mRadius, 2);
    }

    bool BS::isPointInsideSphere(const BS _bs, const Vector3f _point)
    {
        float distanceSqr = (_point.x() - _bs.mX) * (_point.x() - _bs.mX) +
            (_point.y() - _bs.mY) * (_point.y() - _bs.mY) +
            (_point.z() * _bs.mZ) * (_point.z() * _bs.mZ);

        return distanceSqr < std::pow(_bs.mRadius, 2);
    }
}
