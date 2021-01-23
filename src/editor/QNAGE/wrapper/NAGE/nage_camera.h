#ifndef QNAGE_WRAPPER_NAGE_CAMERA_H_
#define QNAGE_WRAPPER_NAGE_CAMERA_H_

#include "engine/components/camera/camera.h"
#include "interface/icamera.h"

namespace mr::qnage
{
    class NAGECamera
        : public ICamera,
          public ISceneObjectTransformation
    {
    public:
        std::string id() const override
        {
            return camera_->id();
        }

        ISceneObjectTransformation* transformation() override
        {
            return this;
        }

        Vec3 translation() const override
        {
            nage::Vector3f translation = camera_->translation();
            return Vec3(translation.x(), translation.y(), translation.z());
        }

        Vec3 rotation() const override
        {
            nage::Quaternion rotation = camera_->rotation();
            nage::Vector3f rotationVector = rotation.vector();
            return Vec3(rotationVector.x(), rotationVector.y(), rotationVector.z());
        }

        void setTranslation(float x, float y , float z) override
        {
            camera_->translate(x, y, z);
        }

        void setRotation(float angle, float x, float y , float z) override
        {
            camera_->rotate(angle, x, y, z);
        }

        Vec3 scale() const override { return VEC3_ZERO; };
        Vec3 shearing() const override { return VEC3_ZERO; };
        void setTranslation(float x, float y) override {}
        void setRotation(float angle, float x, float y) override {}
        void setScale(float x, float y)  override {}
        void setScale(float x, float y , float z) override {}
        void setShearing(float x, float y) override {}
        void setShearing(float x, float y , float z) override {}

        bool isAvailable() override
        {
            return true;
        }

        virtual void onTranslation(std::function<void(ISceneObjectTransformation::Vec3)> _callback)
        {
            translationConsumer_ = _callback;
            camera_->onTranslation([this](nage::Vector3f _update) {
                if(translationConsumer_)
                    translationConsumer_(Vec3(_update.x(), _update.y(), _update.z()));
            });
        }
 
        virtual void onRotation(std::function<void(ISceneObjectTransformation::Vec3)> _callback)
        {
            rotationConsumer_ = _callback;
            camera_->onRotatation([this](nage::Vector3f _update) {
                if(rotationConsumer_)
                    rotationConsumer_(Vec3(_update.x(), _update.y(), _update.z()));
            });
        }

        static NAGECamera* from(nage::Camera* _camera)
        {
            if(!_camera)
                throw new std::invalid_argument("Cannot create item for not defined camera");

            return new NAGECamera(_camera);
        }

    private:
        NAGECamera(nage::Camera* _camera) : camera_(_camera) {}

        nage::Camera* camera_;
        std::function<void(ISceneObjectTransformation::Vec3)> translationConsumer_;
        std::function<void(ISceneObjectTransformation::Vec3)> rotationConsumer_;
    };
}

#endif // QNAGE_WRAPPER_NAGE_CAMERA_H_
