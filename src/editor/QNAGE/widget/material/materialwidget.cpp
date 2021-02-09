#include "materialwidget.h"

namespace mr::qnage
{
    MaterialWidget::MaterialWidget(QWidget* _parent)
        : QWidget(_parent)
    {
        setupUi();
    }

    MaterialWidget::~MaterialWidget()
    {
        delete widgetHeaderBar_;
        delete texturePicker_;
        delete heapmapMaterial_;
        delete spacerItem_;
        delete mainLayout_;
    }

    void MaterialWidget::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout;
        this->setLayout(this->mainLayout_);

        this->widgetHeaderBar_ = new HeaderBar("Material");
        this->mainLayout_->addWidget(this->widgetHeaderBar_);

        this->texturePicker_ = new TexturePicker(this);
        this->mainLayout_->addWidget(this->texturePicker_);
        connect(this->texturePicker_, &TexturePicker::done, [this](QImage _heightmap) {
            this->resourceHandler_->mapTexture("heightmap", _heightmap);
        });

        this->heapmapMaterial_ = new HeapmapMaterial(this);
        this->mainLayout_->addWidget(this->heapmapMaterial_);
        connect(this->heapmapMaterial_, &HeapmapMaterial::done, [this](QMap<HeapMapColor, QImage> _heapMapDefinition, QImage _heapmap) {
            if(this->resourceHandler_)
            {
                this->resourceHandler_->mapTexture("material.blendmap", _heapmap);
                this->resourceHandler_->mapTexture("material.red", _heapMapDefinition[HeapMapColor::Red]);
                this->resourceHandler_->mapTexture("material.green", _heapMapDefinition[HeapMapColor::Green]);
                this->resourceHandler_->mapTexture("material.blue", _heapMapDefinition[HeapMapColor::Blue]);
                this->resourceHandler_->mapTexture("material.alpha", _heapMapDefinition[HeapMapColor::Alpha]);
            }
        });

        this->spacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        this->mainLayout_->addItem(this->spacerItem_);
    }

    void MaterialWidget::setResourceHandler(ISceneResource* _resource)
    {
        // if(!this->resourceHandler_)
            this->resourceHandler_ = _resource;
    }
}
