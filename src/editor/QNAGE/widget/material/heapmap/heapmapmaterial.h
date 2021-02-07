#ifndef QNAGE_WIDGET_MATERIAL_HEAMPMAP_HEAPMAPMATERIAL_H_
#define QNAGE_WIDGET_MATERIAL_HEAMPMAP_HEAPMAPMATERIAL_H_

#include "heapmaptexturepicker.h"

namespace mr::qnage
{
    class HeapmapMaterial
        : public QWidget
    {
        Q_OBJECT

        class HeapMapTexturePickerResult
            : public QWidget
        {
            const QMap<HeapMapColor, QString> colorMap = {
                { HeapMapColor::Red, "red" },
                { HeapMapColor::Green, "green" },
                { HeapMapColor::Blue, "blue" },
                { HeapMapColor::Alpha, "transparent" }
            };

        public:
            explicit HeapMapTexturePickerResult(QWidget* _parent = nullptr)
                : QWidget(_parent)
            {
                this->layout_ = new QVBoxLayout;
                this->setContentsMargins(0, 0, 0, 0);
                this->setLayout(this->layout_);

                this->texturePreview_ = new QLabel(this);
                this->setFixedSize(80, 80);
                this->layout_->addWidget(this->texturePreview_);

                this->colorPreview_ = new QLabel(this);
                this->layout_->addWidget(this->colorPreview_);
            }

            void set(const HeapMapColor _color, const QImage _texture)
            {
                this->texturePreview_->setPixmap(QPixmap::fromImage(_texture).scaled(80, 80, Qt::KeepAspectRatio));
                this->colorPreview_->setStyleSheet("QLabel { background-color: " + colorMap[_color] + "; border: 1px solid white; }");
            }

            ~HeapMapTexturePickerResult()
            {
                delete texturePreview_;
                delete colorPreview_;
            }

        private:
            QVBoxLayout* layout_;
            QLabel* texturePreview_;
            QLabel* colorPreview_;
        };
    
    public:
        explicit HeapmapMaterial(QWidget* _parent = nullptr);
        ~HeapmapMaterial();

    private:
        void setMappersVisibility(bool _state);

        QHBoxLayout* layout_;
        HeapmapTexturePicker* picker_;

        QHBoxLayout* mappersLayout_;
        QSpacerItem* mapperSpacerItem_;
        HeapMapTexturePickerResult *redMapper_, *greenMapper_, *blueMapper_, *alphaMapper_;
    };
}

#endif // QNAGE_WIDGET_MATERIAL_HEAMPMAP_HEAPMAPMATERIAL_H_
