#ifndef QNAGE_SCENE_SCENETREENODEITEM_H_
#define QNAGE_SCENE_SCENETREENODEITEM_H_

#include "scenetreenodeitemtransformations.h"

#include <map>
#include <functional>
#include <QTreeWidgetItem>
#include <QObject>

namespace mr::qnage
{
    class ISceneTreeNodeItem
    {
    public:
        virtual QString name() const = 0;
        virtual ISceneResource* resource() const = 0;
        virtual SceneTreeNodeItemTransformations* transformations() = 0;
    };

    class SceneTreeNodeItem
        : public ISceneTreeNodeItem,
          public QTreeWidgetItem
    {
    public:
        enum class Type
        {
            Camera,
            Light,
            Model
        };

        inline static constexpr const SceneTreeNodeItemTransformations::Type ALL_TRANSFORMATIONS =
            SceneTreeNodeItemTransformations::Type::Translation |
            SceneTreeNodeItemTransformations::Type::Rotation |
            SceneTreeNodeItemTransformations::Type::Scaling |
            SceneTreeNodeItemTransformations::Type::Shearing;

        SceneTreeNodeItem(const Type _type, ISceneObject* _object, SceneTreeNodeItemTransformations::Type transformationType,
                QTreeWidgetItem* _parent = nullptr)
            : QTreeWidgetItem(_parent),
              type_(_type),
              object_(_object),
              transformations_(new SceneTreeNodeItemTransformations(transformationType))
        {
            if(!_object)
                throw new std::invalid_argument("Cannot create item for not defined object");

            this->setText(0, QString::fromStdString(_object->id()));
            setupAsType(_type);

            // Future updates handlers
            QObject::connect(this->transformations_, &SceneTreeNodeItemTransformations::onTranslation,
                [this](float x, float y, float z) {
                    translate(x, y, z);
                });
            QObject::connect(this->transformations_, &SceneTreeNodeItemTransformations::onRotation,
                [this](float x, float y, float z) {
                    rotate(x, y, z);
                });
            QObject::connect(this->transformations_, &SceneTreeNodeItemTransformations::onScaling,
                [this](float x, float y, float z) {
                    scale(x, y, z);
                });
            QObject::connect(this->transformations_, &SceneTreeNodeItemTransformations::onShearing,
                [this](float x, float y, float z) {
                    shear(x, y, z);
                });
        }

        SceneTreeNodeItem(ICamera* _camera, QTreeWidgetItem* _parent = nullptr)
            : SceneTreeNodeItem(Type::Camera, _camera, SceneTreeNodeItemTransformations::Type::Translation, _parent)
        {
            // First update
            setTranslation(_camera->transformation()->translation());

            // Event bus
            _camera->onTranslation(std::bind(&SceneTreeNodeItem::setTranslation, this, std::placeholders::_1));
            // TODO: re-enable rotation section
            // _camera->onRotation(std::bind(&SceneTreeNodeItem::setRotation, this, std::placeholders::_1));
        }

        virtual ~SceneTreeNodeItem()
        {
            delete transformations_;
        }

        QString name() const override
        {
            return QString::fromStdString(object_->id());
        }

        ISceneResource* resource() const override
        {
            if(!object_)
                return nullptr;

            return object_->resource();
        }

        SceneTreeNodeItemTransformations* transformations() override
        {
            return transformations_;
        }

    private slots:
        void setTranslation(ISceneObjectTransformation::Vec3 value)
        {
            transformations_->setTranslation(value.x, value.y, value.z);
        }

        void setRotation(ISceneObjectTransformation::Vec3 value)
        {
            transformations_->setRotation(value.x, value.y, value.z);
        }

        void setScale(ISceneObjectTransformation::Vec3 value)
        {
            transformations_->setScaling(value.x, value.y, value.z);
        }

        void setShearing(ISceneObjectTransformation::Vec3 value)
        {
            transformations_->setShearing(value.x, value.y, value.z);
        }

        void translate(float x, float y , float z)
        {
            if(object_->isTransformable())
                object_->transformation()->setTranslation(x, y, z);
        }

        void rotate(float x, float y , float z)
        {
            if(object_->isTransformable())
                object_->transformation()->setRotation(x, y, z);
        }

        void scale(float x, float y , float z)
        {
            if(object_->isTransformable())
                object_->transformation()->setScale(x, y, z);
        }

        void shear(float x, float y , float z)
        {
            if(object_->isTransformable())
                object_->transformation()->setShearing(x, y, z);
        }

    private:
        Type type_;
        ISceneObject* object_;
        SceneTreeNodeItemTransformations* transformations_;

        std::map<Type, std::function<void()>> typeMap = {
            { Type::Camera, [this]() { setupAsCamera(); } },
            { Type::Light, [this]() { setupAsLight(); } },
            { Type::Model, [this]() { setupAsModel(); } }
        };

        void setupAsType(const Type _type)
        {
            typeMap.at(_type)();
        }

        void setupAsCamera()
        {
            QIcon cameraIcon;
            cameraIcon.addPixmap(QPixmap(":/rc/icons/scene/camera.png"));
            this->setIcon(0, cameraIcon);
        }

        void setupAsLight()
        {
            QIcon lightIcon;
            lightIcon.addPixmap(QPixmap(":/rc/icons/scene/light.png"));
            this->setIcon(0, lightIcon);
        }

        void setupAsModel()
        {
            QIcon modelIcon;
            modelIcon.addPixmap(QPixmap(":/rc/icons/scene/model.png"));
            this->setIcon(0, modelIcon);
        }
    };
}

#endif // QNAGE_SCENE_SCENETREENODEITEM_H_
