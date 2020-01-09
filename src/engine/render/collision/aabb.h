#ifndef NAGE_ENGINE_RENDER_COLISION_AABB_H_
#define NAGE_ENGINE_RENDER_COLISION_AABB_H_

#include "engine/math/NAGEMath/nagemathvector.h"

namespace NAGE
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

        // Per object methods.
        bool intersect(const AABB _box);
        bool intersect(const BS _bs);
        bool isPointInside(const Vector3f _point);

        // Static methods.
        static bool intersect(const AABB _boxA, const AABB _boxB);
        static bool isPointInside(const AABB _box, const Vector3f _point);

    private:
        float mMinX, mMaxX;
        float mMinY, mMaxY;
        float mMinZ, mMaxZ;
    };
}

#endif // NAGE_ENGINE_RENDER_COLISION_AABB_H_
