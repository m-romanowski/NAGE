#ifndef NAGE_ENGINE_RENDER_COLISION_BS_H_
#define NAGE_ENGINE_RENDER_COLISION_BS_H_

#include "engine/math/NAGEMath/nagemathvector.h"

namespace mr::nage
{
    /* Bounding Spheres
     *
     * Reference:
     * (1) https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
     */
    class AABB;

    class BS
    {
    public:
        BS();

        // Getters
        float x() const;
        float y() const;
        float z() const;
        Vector3f point() const;
        float radius() const;

        // Setters
        void setX(float _x);
        void setY(float _y);
        void setZ(float _z);
        void setPoint(const Vector3f _point);
        void setRadius(float _radius);

        // AABB
        bool intersect(const AABB _box);
        bool intersect(const Vector3f _min, const Vector3f _max);
        // BS
        bool intersect(const BS _bs);
        bool intersect(const Vector3f _point, float _radius);
        // Point
        bool isPointInsideSphere(const Vector3f _point);
        bool isPointInsideSphere(float _x, float _y, float _z);

    private:
        float x_, y_, z_; // Sphere position
        float radius_; // Sphere radius
    };
}

#endif // NAGE_ENGINE_RENDER_COLISION_BS_H_
