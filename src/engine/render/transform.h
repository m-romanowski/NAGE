#ifndef NAGE_ENGINE_RENDER_TRANSFORM_H_
#define NAGE_ENGINE_RENDER_TRANSFORM_H_

#include "engine/math/NAGEMath/nagemathvector.h"
#include "engine/math/NAGEMath/nagemathmatrix.h"
#include "engine/math/NAGEMath/nagemathquaternion.h"

namespace mr::nage
{
    class Transform
    {
    public:
        Transform();

        // Getters
        Vector3f translation() const;
        Quaternion rotation() const;
        Vector3f scaling() const;
        Vector3f shearing() const;

        // Setters
        void setTranslation(const Vector3f& _translation);
        void setTranslation(float _dx, float _dy, float _dz);
        void setScale(const Vector3f& _scaling);
        void setScale(float _dx, float _dy, float _dz);
        void setScale(float _factor);
        void setRotation(const Quaternion& _rotation);
        void setRotation(float _angle, const Vector3f& _axis);
        void setRotation(float _angle, float _ax, float _ay, float _az);
        void setShearing(const Vector3f& _shearing);
        void setShearing(float _dx, float _dy, float _dz);

        void translate(const Vector3f& _dt);
        void translate(float _dx, float _dy, float _dz);
        void scale(const Vector3f& _ds);
        void scale(float _dx, float _dy, float _dz);
        void scale(float _factor);
        void rotate(const Quaternion& _rotation);
        void rotate(float _angle, const Vector3f& _axis);
        void rotate(float _angle, float _ax, float _ay, float _az);
        void shear(const Vector3f& _ds);
        void shear(float _dx, float _dy, float _dz);
        void shear(float _factor);

        Matrix4f model() const;

    private:
        Vector3f translation_;
        Vector3f scaling_;
        Vector3f shearing_;
        Quaternion rotation_;
    };
}

#endif // NAGE_ENGINE_RENDER_TRANSFORM_H_
