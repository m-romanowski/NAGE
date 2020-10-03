#include "projection.h"

namespace mr::nage
{
    Projection::Projection()
        : fov_(60.0f),
          aspectRatio_(static_cast<float>(800) / static_cast<float>(600)),
          top_(0),
          bottom_(0),
          left_(0),
          right_(0),
          zNear_(0.1f),
          zFar_(1000.0f)
    {

    }

    float Projection::fov() const
    {
        return fov_;
    }

    float Projection::aspectRatio() const
    {
        return aspectRatio_;
    }

    float Projection::top() const
    {
        return top_;
    }

    float Projection::bottom() const
    {
        return bottom_;
    }

    float Projection::left() const
    {
        return left_;
    }

    float Projection::right() const
    {
        return right_;
    }

    float Projection::zNear() const
    {
        return zNear_;
    }

    float Projection::zFar() const
    {
        return zFar_;
    }

    void Projection::setFov(const float _fov)
    {
        fov_ = _fov;
    }

    void Projection::setAspectRatio(const float _aspectRatio)
    {
        aspectRatio_ = _aspectRatio;
    }

    void Projection::setAspectRatio(const int _width, const int _height)
    {
        aspectRatio_ = static_cast<float>(_width) / static_cast<float>(_height);
    }

    void Projection::setTop(const float _top)
    {
        top_ = _top;
    }

    void Projection::setBottom(const float _bottom)
    {
        bottom_ = _bottom;
    }

    void Projection::setLeft(const float _left)
    {
        left_ = _left;
    }

    void Projection::setRight(const float _right)
    {
        right_ = _right;
    }

    void Projection::setZNear(const float _zNear)
    {
        zNear_ = _zNear;
    }

    void Projection::setZFar(const float _zFar)
    {
        zFar_ = _zFar;
    }

    Matrix4f Projection::perspective() const
    {
        Matrix4f perspectiveMatrix;
        perspectiveMatrix.identity();
        perspectiveMatrix.perspective(fov_, aspectRatio_, zNear_, zFar_);

        return perspectiveMatrix;
    }

    Matrix4f Projection::orthographic() const
    {
        Matrix4f orthographicMatrix;
        orthographicMatrix.identity();
        orthographicMatrix.orthographic(left_, right_, top_, bottom_, zNear_, zFar_);

        return orthographicMatrix;
    }
}
