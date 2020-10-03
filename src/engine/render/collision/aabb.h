#ifndef NAGE_ENGINE_RENDER_COLISION_AABB_H_
#define NAGE_ENGINE_RENDER_COLISION_AABB_H_

#include "engine/math/NAGEMath/nagemathvector.h"

namespace mr::nage
{
    /* Axis aligned bounding box
     *
     * Reference:
     * (1) https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
     */
    class BS;

    class AABB
    {
    public:
        AABB();

        // Getters
        float minX() const;
        float maxX() const;
        float minY() const;
        float maxY() const;
        float minZ() const;
        float maxZ() const;
        Vector3f min() const;
        Vector3f max() const;
        Vector3f center() const;
        Vector3f extent() const;

        // Setters
        void setMinX(float _x);
        void setMaxX(float _x);
        void setMinY(float _y);
        void setMaxY(float _y);
        void setMinZ(float _z);
        void setMaxZ(float _z);
        void setX(float _minX, float _maxX);
        void setY(float _minY, float _maxY);
        void setZ(float _minZ, float _maxZ);
        void setMin(const Vector3f _min);
        void setMax(const Vector3f _max);
        void setMinMax(const Vector3f _min, const Vector3f _max);

        // AABB
        bool intersect(const AABB _box);
        bool intersect(const Vector3f _min, const Vector3f _max);
        // BS
        bool intersect(const BS _bs);
        bool intersect(const Vector3f _point, float _radius);
        // Point
        bool isPointInside(const Vector3f _point);
        bool isPointInside(float _x, float _y, float _z);

    private:
        float minX_, maxX_;
        float minY_, maxY_;
        float minZ_, maxZ_;
    };
}

#endif // NAGE_ENGINE_RENDER_COLISION_AABB_H_
