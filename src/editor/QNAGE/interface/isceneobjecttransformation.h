#ifndef QNAGE_INTERFACE_ISCENETRANSFORMATION_H_
#define QNAGE_INTERFACE_ISCENETRANSFORMATION_H_

namespace mr::qnage
{    
    class ISceneObjectTransformation
    {
    public:
        struct Vec2
        {
            float x, y;

            Vec2(float x, float y)
            {
                this->x = x;
                this->y = y;
            }
        };

        struct Vec3
        {
            float x, y, z;

            Vec3(float x, float y, float z)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }
        };

        virtual Vec3 translation() const = 0;
        virtual Vec3 rotation() const = 0;
        virtual Vec3 scale() const = 0;
        virtual Vec3 shearing() const = 0;

        virtual void setTranslation(float x, float y) = 0;
        virtual void setTranslation(float x, float y , float z) = 0;
        virtual void setRotation(float angle, float x, float y) = 0;
        virtual void setRotation(float angle, float x, float y , float z) = 0;
        virtual void setScale(float x, float y) = 0;
        virtual void setScale(float x, float y , float z) = 0;
        virtual void setShearing(float x, float y) = 0;
        virtual void setShearing(float x, float y , float z) = 0;
        virtual bool isAvailable() = 0;

        virtual void setTranslation(const Vec2 vec)
        {
            setTranslation(vec.x, vec.y);
        }

        virtual void setTranslation(const Vec3 vec)
        {
            setTranslation(vec.x, vec.y, vec.z);
        }

        virtual void setRotation(float angle, const Vec2 vec)
        {
            setRotation(angle, vec.x, vec.y);
        }

        virtual void setRotation(float angle, const Vec3 vec)
        {
            setRotation(angle, vec.x, vec.y, vec.z);
        }

        virtual void setScale(const Vec2 vec)
        {
            setScale(vec.x, vec.y);
        }

        virtual void setScale(const Vec3 vec)
        {
            setScale(vec.x, vec.y, vec.z);
        }

        virtual void setShearing(const Vec2 vec)
        {
            setShearing(vec.x, vec.y);
        }

        virtual void setShearing(const Vec3 vec)
        {
            setShearing(vec.x, vec.y, vec.z);
        }

        inline const static Vec2 VEC2_ZERO = Vec2(0.0f, 0.0f);
        inline const static Vec3 VEC3_ZERO = Vec3(0.0f, 0.0f, 0.0f);
    };
}

#endif // QNAGE_INTERFACE_ISCENETRANSFORMATION_H_
