#include "transform.h"

namespace mr::nage
{
    Transform::Transform()
        : translation_(Vector3f(0.0f, 0.0f, 0.0f)),
          scaling_(Vector3f(1.0f, 1.0f, 1.0f)),
          shearing_(Vector3f(0.0f, 0.0f, 0.0f)),
          rotation_(Quaternion(0.0f, 0.0f, 0.0f, 1.0f))
    {

    }

    Vector3f Transform::translation() const
    {
        return translation_;
    }

    Quaternion Transform::rotation() const
    {
        return rotation_;
    }

    Vector3f Transform::scaling() const
    {
        return scaling_;
    }

    Vector3f Transform::shearing() const
    {
        return shearing_;
    }

    void Transform::setTranslation(const Vector3f& _translation)
    {
        translation_ = _translation;
    }

    void Transform::setTranslation(float _dx, float _dy, float _dz)
    {
        setTranslation(Vector3f(_dx, _dy, _dz));
    }

    void Transform::setScale(const Vector3f& _scaling)
    {
        scaling_ = _scaling;
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
        rotation_ = _rotation;
    }

    void Transform::setRotation(float _angle, const Vector3f& _axis)
    {
        setRotation(Quaternion::fromAxisAndAngle(_angle, _axis));
    }

    void Transform::setRotation(float _angle, float _ax, float _ay, float _az)
    {
        setRotation(Quaternion::fromAxisAndAngle(_angle, _ax, _ay, _az));
    }

    void Transform::setShearing(const Vector3f& _shearing)
    {
        shearing_ = _shearing;
    }

    void Transform::setShearing(float _dx, float _dy, float _dz)
    {
        setShearing(Vector3f(_dx, _dy, _dz));
    }

    void Transform::translate(const Vector3f& _dt)
    {
        translation_ += _dt;
    }

    void Transform::translate(float _dx, float _dy, float _dz)
    {
        translate(Vector3f(_dx, _dy, _dz));
    }

    void Transform::scale(const Vector3f& _ds)
    {
        scaling_ = Vector3f(scaling_.x() * _ds.x(), scaling_.y() * _ds.y(),
            scaling_.z() * _ds.z());
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
        rotation_ = _rotation * rotation_;
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
        shearing_ = Vector3f(scaling_.x() * _ds.x(), scaling_.y() * _ds.y(),
            scaling_.z() * _ds.z());
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
        matrix.translate(translation_);
        matrix.rotate(rotation_);
        matrix.scale(scaling_);
        matrix.shear(shearing_);

        return matrix;
    }
}
