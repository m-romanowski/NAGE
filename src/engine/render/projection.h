#ifndef NAGE_ENGINE_RENDER_PROJECTION_H_
#define NAGE_ENGINE_RENDER_PROJECTION_H_

#include "engine/math/NAGEMath/nagemathmatrix.h"

namespace NAGE
{
    class Projection
    {
    public:
        Projection();

        // Getters
        float fov() const;
        float aspectRatio() const;
        float top() const;
        float bottom() const;
        float left() const;
        float right() const;
        float zNear() const;
        float zFar() const;

        // Setters
        void setFov(const float _fov);
        void setAspectRatio(const float _aspectRatio);
        void setAspectRatio(const int _width, const int _height);
        void setTop(const float _top);
        void setBottom(const float _bottom);
        void setLeft(const float _left);
        void setRight(const float _right);
        void setZNear(const float _zNear);
        void setZFar(const float _zFar);

        Matrix4f perspective() const;
        Matrix4f orthographic() const;
    private:
        // Perspective
        float mFov;
        float mAspectRatio;

        // Orthographic
        float mTop, mBottom;
        float mLeft, mRight;

        // Common
        float mZNear, mZFar;
    };
}

#endif // NAGE_ENGINE_RENDER_PROJECTION_H_
