#include "heapmapmaterial.h"

namespace mr::qnage
{
    HeapmapMaterial::HeapmapMaterial(QWidget* _parent)
        : QWidget(_parent)
    {
        this->layout_ = new QHBoxLayout;
        this->layout_->setContentsMargins(0, 0, 0, 0);
        this->setLayout(this->layout_);

        this->picker_ = new HeapmapTexturePicker(this);
        this->layout_->addWidget(this->picker_);
        connect(this->picker_, &HeapmapTexturePicker::done, [this]() {
            QMap<HeapMapColor, QImage> result = this->picker_->heapmapDefinition();
            this->redMapper_->set(HeapMapColor::Red, result[HeapMapColor::Red]);
            this->greenMapper_->set(HeapMapColor::Green, result[HeapMapColor::Green]);
            this->blueMapper_->set(HeapMapColor::Blue, result[HeapMapColor::Blue]);
            this->alphaMapper_->set(HeapMapColor::Alpha, result[HeapMapColor::Alpha]);

            setMappersVisibility(true);
            emit done(result, QImage(*texture()));
        });

        this->mappersLayout_ = new QHBoxLayout;
        this->mappersLayout_->setContentsMargins(0, 0, 0, 0);
        this->layout_->addLayout(this->mappersLayout_);

        this->redMapper_ = new HeapMapTexturePickerResult(this);
        this->mappersLayout_->addWidget(this->redMapper_);

        this->greenMapper_ = new HeapMapTexturePickerResult(this);
        this->mappersLayout_->addWidget(this->greenMapper_);

        this->blueMapper_ = new HeapMapTexturePickerResult(this);
        this->mappersLayout_->addWidget(this->blueMapper_);

        this->alphaMapper_ = new HeapMapTexturePickerResult(this);
        this->mappersLayout_->addWidget(this->alphaMapper_);

        this->mapperSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        this->mappersLayout_->addItem(this->mapperSpacerItem_);

        setMappersVisibility(false);
    }

    HeapmapMaterial::~HeapmapMaterial()
    {
        delete redMapper_;
        delete greenMapper_;
        delete blueMapper_;
        delete alphaMapper_;
        delete mapperSpacerItem_;
        delete mappersLayout_;
        delete layout_;
    }

    void HeapmapMaterial::setMappersVisibility(bool _state)
    {
        if(!this->mappersLayout_)
            return;

        for(int i = 0; i < this->mappersLayout_->count() - 1; ++i)
        {
            QWidget* child = this->mappersLayout_->itemAt(i)->widget();
            child->setVisible(_state);
        }
    }

    QImage* HeapmapMaterial::texture()
    {
        return picker_->image();
    }
}
