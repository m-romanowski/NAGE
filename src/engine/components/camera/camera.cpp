#include "camera.h"

namespace NAGE
{
    Camera::Camera()
        : mForward(Vector3f::forward),
          mUp(Vector3f::up),
          mRight(Vector3f::right)
    {

    }

    void Camera::translate(const Vector3f& _translation)
    {
        mTranslation += _translation;
    }

    void Camera::translate(float _x, float _y, float _z)
    {
        translate(Vector3f(_x, _y, _z));
    }

    void Camera::rotate(const Quaternion& _rotation)
    {
        mRotation = _rotation * mRotation;
    }

    void Camera::rotate(float _angle, const Vector3f& _axis)
    {
        rotate(Quaternion::fromAxisAndAngle(_angle, _axis));
    }

    void Camera::rotate(float _angle, float _x, float _y, float _z)
    {
        rotate(Quaternion::fromAxisAndAngle(_angle, _x, _y, _z));
    }

    void Camera::setForward(const Vector3f& _forward)
    {
        mForward = _forward;
    }

    void Camera::setUp(const Vector3f& _up)
    {
        mUp = _up;
    }

    void Camera::setRight(const Vector3f& _right)
    {
        mRight = _right;
    }

    void Camera::setTranslation(const Vector3f& _translation)
    {
        mTranslation = _translation;
    }

    void Camera::setTranslation(float _x, float _y, float _z)
    {
        mTranslation = Vector3f(_x, _y, _z);
    }

    void Camera::setRotation(const Quaternion& _rotation)
    {
        mRotation = _rotation;
    }

    void Camera::setRotation(float _angle, const Vector3f& _axis)
    {
        setRotation(Quaternion::fromAxisAndAngle(_angle, _axis));
    }

    void Camera::setRotation(float _angle, float _x, float _y, float _z)
    {
        setRotation(Quaternion::fromAxisAndAngle(_angle, Vector3f(_x, _y, _z)));
    }

    Vector3f Camera::forward() const
    {
        return mRotation.rotatedVector(mForward);
    }

    Vector3f Camera::up() const
    {
        return mRotation.rotatedVector(mUp);
    }

    Vector3f Camera::right() const
    {
        return mRotation.rotatedVector(mRight);
    }

    Matrix4f Camera::view() const
    {
        Matrix4f view;
        view.identity();
        view.rotate(mRotation.conjugate());
        view.translate(-mTranslation);

        return view;
    }
}
