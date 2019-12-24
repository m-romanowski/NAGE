#include "projection.h"

namespace NAGE
{
    Projection::Projection()
        : mFov(60.0f),
          mAspectRatio(static_cast<float>(800) / static_cast<float>(600)),
          mTop(0),
          mBottom(0),
          mLeft(0),
          mRight(0),
          mZNear(0.1f),
          mZFar(1000.0f)
    {

    }

    float Projection::fov() const
    {
        return mFov;
    }

    float Projection::aspectRatio() const
    {
        return mAspectRatio;
    }

    float Projection::top() const
    {
        return mTop;
    }

    float Projection::bottom() const
    {
        return mBottom;
    }

    float Projection::left() const
    {
        return mLeft;
    }

    float Projection::right() const
    {
        return mRight;
    }

    float Projection::zNear() const
    {
        return mZNear;
    }

    float Projection::zFar() const
    {
        return mZFar;
    }

    void Projection::setFov(const float _fov)
    {
        mFov = _fov;
    }

    void Projection::setAspectRatio(const float _aspectRatio)
    {
        mAspectRatio = _aspectRatio;
    }

    void Projection::setAspectRatio(const int _width, const int _height)
    {
        mAspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
    }

    void Projection::setTop(const float _top)
    {
        mTop = _top;
    }

    void Projection::setBottom(const float _bottom)
    {
        mBottom = _bottom;
    }

    void Projection::setLeft(const float _left)
    {
        mLeft = _left;
    }

    void Projection::setRight(const float _right)
    {
        mRight = _right;
    }

    void Projection::setZNear(const float _zNear)
    {
        mZNear = _zNear;
    }

    void Projection::setZFar(const float _zFar)
    {
        mZFar = _zFar;
    }

    Matrix4f Projection::perspective() const
    {
        Matrix4f perspectiveMatrix;
        perspectiveMatrix.identity();
        perspectiveMatrix.perspective(mFov, mAspectRatio, mZNear, mZFar);

        return perspectiveMatrix;
    }

    Matrix4f Projection::orthographic() const
    {
        Matrix4f orthographicMatrix;
        orthographicMatrix.identity();
        orthographicMatrix.orthographic(mLeft, mRight, mTop, mBottom, mZNear, mZFar);

        return orthographicMatrix;
    }
}
