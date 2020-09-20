#include "camera.h"

namespace NAGE
{
    Camera::Camera()
        : forward_(Vector3f::forward),
          up_(Vector3f::up),
          right_(Vector3f::right)
    {

    }

    void Camera::translate(const Vector3f& _translation)
    {
        translation_ = _translation + translation_;
    }

    void Camera::translate(float _x, float _y, float _z)
    {
        translate(Vector3f(_x, _y, _z));
    }

    void Camera::rotate(const Quaternion& _rotation)
    {
        rotation_ = _rotation * rotation_;
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
        forward_ = _forward;
    }

    void Camera::setUp(const Vector3f& _up)
    {
        up_ = _up;
    }

    void Camera::setRight(const Vector3f& _right)
    {
        right_ = _right;
    }

    void Camera::setTranslation(const Vector3f& _translation)
    {
        translation_ = _translation;
    }

    void Camera::setTranslation(float _x, float _y, float _z)
    {
        translation_ = Vector3f(_x, _y, _z);
    }

    void Camera::setRotation(const Quaternion& _rotation)
    {
        rotation_ = _rotation;
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
        return rotation_.rotatedVector(forward_);
    }

    Vector3f Camera::up() const
    {
        return rotation_.rotatedVector(up_);
    }

    Vector3f Camera::right() const
    {
        return rotation_.rotatedVector(right_);
    }

    Vector3f Camera::translation() const
    {
        return translation_;
    }

    Quaternion Camera::rotation() const
    {
        return rotation_;
    }

    float Camera::roll() const
    {
        return std::atan2(
                    2.0f * rotation_.y() * rotation_.w() - 2.0f * rotation_.x() * rotation_.z(),
                    1.0f - 2.0f * rotation_.y() * rotation_.y() - 2.0f * rotation_.z() * rotation_.z());
    }

    float Camera::pitch() const
    {
        return std::atan2(
                    2.0f * rotation_.x() * rotation_.w() - 2.0f * rotation_.y() * rotation_.z(),
                    1.0f - 2.0f * rotation_.x() * rotation_.x() - 2.0f * rotation_.z() * rotation_.z());
    }

    float Camera::yaw() const
    {
        return std::asin(2.0f * rotation_.x() * rotation_.y() + 2.0f * rotation_.z() * rotation_.w());
    }

    Matrix4f Camera::view() const
    {
        Matrix4f view;
        view.identity();
        view.rotate(rotation_.conjugate());
        view.translate(-translation_);

        return view;
    }
}
