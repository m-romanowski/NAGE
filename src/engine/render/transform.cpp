#include "transform.h"

namespace NAGE
{
    Transform::Transform()
        : mTranslation(Vector3f(0.0f, 0.0f, 0.0f)),
          mScaling(Vector3f(1.0f, 1.0f, 1.0f)),
          mShearing(Vector3f(0.0f, 0.0f, 0.0f)),
          mRotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f))
    {

    }

    Vector3f Transform::translation() const
    {
        return mTranslation;
    }

    Quaternion Transform::rotation() const
    {
        return mRotation;
    }

    Vector3f Transform::scaling() const
    {
        return mScaling;
    }

    Vector3f Transform::shearing() const
    {
        return mShearing;
    }

    void Transform::setTranslation(const Vector3f& _translation)
    {
        mTranslation = _translation;
    }

    void Transform::setTranslation(float _dx, float _dy, float _dz)
    {
        setTranslation(Vector3f(_dx, _dy, _dz));
    }

    void Transform::setScale(const Vector3f& _scaling)
    {
        mScaling = _scaling;
    }

    void Transform::setScale(float _dx, float _dy, float _dz)
    {
        setScale(Vector3f(_dx, _dy, _dz));
    }

    void Transform::setScale(float _factor)
    {
        setScale(Vector3f(_factor, _factor, _factor));
    }

    void Transform::setRotation(const Quaternion& _rotation)
    {
        mRotation = _rotation;
    }

    void Transform::setRotation(float _angle, const Vector3f& _axis)
    {
        setRotation(Quaternion::fromAxisAndAngle(_angle, _axis));
    }

    void Transform::setRotation(float _angle, float _ax, float _ay, float _az)
    {
        setRotation(Quaternion::fromAxisAndAngle(_angle, _ax, _ay, _az));
    }

    void Transform::translate(const Vector3f& _dt)
    {
        mTranslation += _dt;
    }

    void Transform::translate(float _dx, float _dy, float _dz)
    {
        translate(Vector3f(_dx, _dy, _dz));
    }

    void Transform::scale(const Vector3f& _ds)
    {
        mScaling = Vector3f(mScaling.x() * _ds.x(), mScaling.y() * _ds.y(),
            mScaling.z() * _ds.z());
    }

    void Transform::scale(float _dx, float _dy, float _dz)
    {
        scale(Vector3f(_dx, _dy, _dz));
    }

    void Transform::scale(float _factor)
    {
        scale(Vector3f(_factor, _factor, _factor));
    }

    void Transform::rotate(const Quaternion& _rotation)
    {
        mRotation = _rotation * mRotation;
    }

    void Transform::rotate(float _angle, const Vector3f& _axis)
    {
        rotate(Quaternion::fromAxisAndAngle(_angle, _axis));
    }

    void Transform::rotate(float _angle, float _ax, float _ay, float _az)
    {
        rotate(Quaternion::fromAxisAndAngle(_angle, _ax, _ay, _az));
    }

    void Transform::shear(const Vector3f& _ds)
    {
        mShearing = Vector3f(mScaling.x() * _ds.x(), mScaling.y() * _ds.y(),
            mScaling.z() * _ds.z());
    }

    void Transform::shear(float _dx, float _dy, float _dz)
    {
        shear(Vector3f(_dx, _dy, _dz));
    }

    void Transform::shear(float _factor)
    {
        shear(Vector3f(_factor, _factor, _factor));
    }

    Matrix4f Transform::model() const
    {
        Matrix4f matrix;
        matrix.identity();
        matrix.translate(mTranslation);
        matrix.rotate(mRotation);
        matrix.scale(mScaling);
        matrix.shear(mShearing);

        return matrix;
    }
}
