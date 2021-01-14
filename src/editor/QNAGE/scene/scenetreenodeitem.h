#ifndef QNAGE_SCENE_SCENETREEITEM_H_
#define QNAGE_SCENE_SCENETREEITEM_H_

#include "engine/render/renderableobject.h"

#include <QTreeWidgetItem>
#include <map>
#include <functional>

namespace mr::qnage
{
    template <typename T>
    class SceneTreeNodeItem
        : public QTreeWidgetItem
    {
    protected:
        enum class Type
        {
            Camera,
            Light,
            Model
        };

        SceneTreeNodeItem(const Type _type, const QString _name, T* _object, QTreeWidgetItem* _parent = nullptr)
            : QTreeWidgetItem(_parent),
              type_(_type),
              object_(_object)
        {
            this->setText(0, _name);
            setupAsType(_type);
        }

        Type type_;
        T* object_;

    public:
        QString name() const
        {
            return QString::fromStdString(object_->id());
        }

    private:
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

    class RenderableSceneTreeNodeItem
        : public SceneTreeNodeItem<nage::RenderableObject>
    {
    public:
        RenderableSceneTreeNodeItem(nage::RenderableObject* _object, QTreeWidgetItem* _parent = nullptr)
            : SceneTreeNodeItem(SceneTreeNodeItem::Type::Model, QString::fromStdString(_object->id()), _object, _parent)
        {
        }
    };

    class CameraSceneTreeNodeItem
        : public SceneTreeNodeItem<nage::Camera>
    {
    public:
        CameraSceneTreeNodeItem(nage::Camera* _object, QTreeWidgetItem* _parent = nullptr)
            : SceneTreeNodeItem(SceneTreeNodeItem::Type::Camera, "Camera", _object, _parent)
        {
        }
    };
}

#endif // QNAGE_SCENE_SCENETREEITEM_H_
