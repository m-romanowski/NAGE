#ifndef NAGE_ENGINE_RENDER_COLISION_COLLISIONPLANE_H_
#define NAGE_ENGINE_RENDER_COLISION_COLLISIONPLANE_H_

#include "engine/math/NAGEMath/nagemathvector.h"

namespace mr::nage
{
    class CollisionPlane
    {
    public:
        CollisionPlane();

        // Getters
        float a() const;
        float b() const;
        float c() const;
        float d() const;
        float distance() const; // alias for d() method.
        Vector4f vector4() const; // Vector3f(mA, mB, mC. md)
        Vector3f vector3() const; // Vector3f(mA, mB, mC)

        // Setters
        void setA(float _a);
        void setB(float _b);
        void setC(float _c);
        void setD(float _d);
        void setVector(const Vector4f _vector);

        float dotCoord(float _x, float _y, float _z);
        float dotCoord(const Vector3f _point);
        void normalize();

    private:
        float a_, b_, c_, d_;
    };
}

#endif // NAGE_ENGINE_RENDER_COLISION_COLLISIONPLANE_H_
