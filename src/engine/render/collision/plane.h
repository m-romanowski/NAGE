#ifndef NAGE_ENGINE_RENDER_COLISION_PLANE_H_
#define NAGE_ENGINE_RENDER_COLISION_PLANE_H_

#include "engine/math/NAGEMath/nagemathvector.h"

namespace NAGE
{
    class Plane
    {
    public:
        Plane();

        // Getters
        float a() const;
        float b() const;
        float c() const;
        float d() const;

        // Setters
        void setA(float _a);
        void setB(float _b);
        void setC(float _c);
        void setD(float _d);

        float dotCoord(float _x, float _y, float _z);
        float dotCoord(const Vector3f _point);
        void normalize(); // TODO

    private:
        float mA, mB, mC, mD;
    };
}

#endif // NAGE_ENGINE_RENDER_COLISION_PLANE_H_
