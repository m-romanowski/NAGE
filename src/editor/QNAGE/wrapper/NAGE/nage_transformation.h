#ifndef QNAGE_WRAPPER_NAGE_SCENEOBJECTTRANSFORMATION_H_
#define QNAGE_WRAPPER_NAGE_SCENEOBJECTTRANSFORMATION_H_

#include <optional>
#include "engine/render/transform.h"
#include "interface/isceneobjecttransformation.h"

namespace mr::qnage
{
    class NAGESceneObjectTransformation
        : public ISceneObjectTransformation
    {
    public:
        Vec3 translation() const override
        {
            if(transform_.has_value())
            {
                nage::Vector3f translation = transform_.value()->translation();
                return Vec3(translation.x(), translation.y(), translation.z());
            }

            return VEC3_ZERO;
        }

        Vec3 rotation() const override
        {
            if(transform_.has_value())
            {
                nage::Quaternion rotation = transform_.value()->rotation();
                nage::Vector3f rotationVector = rotation.vector();
                return Vec3(rotationVector.x(), rotationVector.y(), rotationVector.z());
            }

            return VEC3_ZERO;
        }

        Vec3 scale() const override
        {
            if(transform_.has_value())
            {
                nage::Vector3f scale = transform_.value()->scaling();
                return Vec3(scale.x(), scale.y(), scale.z());
            }

            return VEC3_ZERO;
        }

        Vec3 shearing() const override
        {
            if(transform_.has_value())
            {
                nage::Vector3f shearing = transform_.value()->shearing();
                return Vec3(shearing.x(), shearing.y(), shearing.z());
            }

            return VEC3_ZERO;
        }

        void setTranslation(float x, float y , float z) override
        {
            if(transform_.has_value())
                transform_.value()->setTranslation(x, y, z);
        }

        void setRotation(float angle, float x, float y , float z) override
        {
            if(transform_.has_value())
                transform_.value()->setRotation(angle, x, y, z);
        }

        void setScale(float x, float y , float z) override
        {
            if(transform_.has_value())
                transform_.value()->setScale(x, y, z);
        }

        void setShearing(float x, float y , float z) override
        {
            if(transform_.has_value())
                transform_.value()->setShearing(x, y, z);
        }

        bool isAvailable() override
        {
            return transform_.has_value();
        }

        void setTranslation(float x, float y) override {}
        void setRotation(float angle, float x, float y) override {}
        void setScale(float x, float y)  override {}
        void setShearing(float x, float y) override {}

        static NAGESceneObjectTransformation* from(nage::Transform* _transform)
        {
            return new NAGESceneObjectTransformation(_transform);
        }

    private:
        static std::optional<nage::Transform*> validate(nage::Transform* _transform)
        {
            if(_transform)
                return std::optional<nage::Transform*>{ _transform };

            return std::nullopt;
        }
    
        NAGESceneObjectTransformation(nage::Transform* _transform)
            : transform_(NAGESceneObjectTransformation::validate(_transform)) {}

        std::optional<nage::Transform*> transform_;
    };
}

#endif // QNAGE_WRAPPER_NAGE_SCENEOBJECTTRANSFORMATION_H_
