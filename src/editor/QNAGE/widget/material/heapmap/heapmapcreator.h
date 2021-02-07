#ifndef QNAGE_WIDGET_MATERIAL_HEAMPMAP_HEAPMAPCREATOR_H_
#define QNAGE_WIDGET_MATERIAL_HEAMPMAP_HEAPMAPCREATOR_H_

#include "editor/QNAGE/widget/material/texture/texturepicker.h"
#include "editor/QNAGE/widget/material/texture/texturepickerdialogbuttonsarea.h"

#include <QGroupBox>
#include <QPalette>
#include <QMap>
#include <QSpacerItem>

namespace mr::qnage
{
    enum class HeapMapColor
    {
        Red,
        Green,
        Blue,
        Alpha
    };

    class HeapmapCreatorStep
        : public QWidget
    {
        Q_OBJECT

    public:
        explicit HeapmapCreatorStep(const QString _sectionTitle, QWidget* _parent = nullptr)
            : QWidget(_parent)
        {
            this->layout_ = new QVBoxLayout;
            this->setLayout(this->layout_);

            this->sectionLayout_ = new QHBoxLayout;
            this->section_ = new QGroupBox(_sectionTitle);
            this->section_->setLayout(this->sectionLayout_);
            this->layout_->addWidget(this->section_);
        }

        virtual ~HeapmapCreatorStep()
        {
            delete sectionLayout_;
            delete section_;
            delete layout_;
        }

    protected:
        void addItem(QWidget* _child)
        {
            this->sectionLayout_->addWidget(_child);
        }

        void addItem(QLayout* _child)
        {
            this->sectionLayout_->addLayout(_child);
        }

        void addItem(QLayoutItem* _child)
        {
            this->sectionLayout_->addItem(_child);
        }

    private:
        QVBoxLayout* layout_;
        QGroupBox* section_;
        QHBoxLayout* sectionLayout_;
    };

    class HeapmapCreatorFirstStep
        : public HeapmapCreatorStep
    {
        Q_OBJECT

    public:
        explicit HeapmapCreatorFirstStep(QWidget* _parent = nullptr)
            : HeapmapCreatorStep("Heightmap", _parent)
        {
            this->leftSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            addItem(this->leftSpacerItem_);

            this->heightMapTexturePicker_ = new TexturePicker(this);
            addItem(this->heightMapTexturePicker_);
            connect(this->heightMapTexturePicker_, &TexturePicker::done, this, [this]() {
                QImage heightmap = QImage(*this->heightMapTexturePicker_->image());
                emit imageSelected(heightmap);
            });

            this->rightSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            addItem(this->rightSpacerItem_);
        }

        ~HeapmapCreatorFirstStep()
        {
            delete leftSpacerItem_;
            delete rightSpacerItem_;
            delete heightMapTexturePicker_;
        }

    signals:
        void imageSelected(QImage _heightmapImage);

    private:
        TexturePicker* heightMapTexturePicker_;
        QSpacerItem *leftSpacerItem_, *rightSpacerItem_;
    };

    class HeapmapCreatorSecondStep
        : public HeapmapCreatorStep
    {
        Q_OBJECT

        class ColorizedLabel
            : public QLabel
        {
        public:
            explicit ColorizedLabel(const QString _backgroundColor, QWidget* _parent)
                : QLabel(_parent)
            {
                this->setFixedSize(50, 50);
                this->setStyleSheet("QLabel { background-color: " + _backgroundColor + "; border: 1px solid white; }");
            }
        };

        struct Color
        {
            double r, g, b;

            Color(double r, double g, double b)
            {
                this->r = r;
                this->g = g;
                this->b = b;
            }
        };

    public:
        explicit HeapmapCreatorSecondStep(QWidget* _parent = nullptr)
            : HeapmapCreatorStep("Heapmap definition", _parent),
              heapmapImage_(nullptr)
        {
            this->leftSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            addItem(this->leftSpacerItem_);

            this->heapmapTexture_ = new QLabel(this);
            this->heapmapTexture_->setFixedSize(80, 80);
            // this->heapmapTexture_->setEnabled(false);
            addItem(this->heapmapTexture_);

            this->rightSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            addItem(this->rightSpacerItem_);

            this->heapmapDefinitionLayout_ = new QGridLayout;
            addItem(this->heapmapDefinitionLayout_);

            this->redColorLabel_ = new ColorizedLabel("red", this);
            this->heapmapDefinitionLayout_->addWidget(this->redColorLabel_, 0, 0);
            this->redColorMappedTexture_ = new TexturePicker(this);
            this->heapmapDefinitionLayout_->addWidget(this->redColorMappedTexture_, 0, 1);
            connect(this->redColorMappedTexture_, &TexturePicker::done, [this]() {
                this->heapmapDefinictions_.insert(HeapMapColor::Red, QImage(*this->redColorMappedTexture_->image()));
                if(this->heapmapDefinictions_.size() >= 4 && heapmapImage_)
                    emit done(this->heapmapDefinictions_, QImage(*heapmapImage_));
            });

            this->greenColorLabel_ = new ColorizedLabel("green", this);
            this->heapmapDefinitionLayout_->addWidget(this->greenColorLabel_, 1, 0);
            this->greenColorMappedTexture_ = new TexturePicker(this);
            this->heapmapDefinitionLayout_->addWidget(this->greenColorMappedTexture_, 1, 1);
            connect(this->greenColorMappedTexture_, &TexturePicker::done, [this]() {
                this->heapmapDefinictions_.insert(HeapMapColor::Green, QImage(*this->greenColorMappedTexture_->image()));
                if(this->heapmapDefinictions_.size() >= 4 && heapmapImage_)
                    emit done(this->heapmapDefinictions_, QImage(*heapmapImage_));
            });

            this->blueColorLabel_ = new ColorizedLabel("blue", this);
            this->heapmapDefinitionLayout_->addWidget(this->blueColorLabel_, 2, 0);
            this->blueColorMappedTexture_ = new TexturePicker(this);
            this->heapmapDefinitionLayout_->addWidget(this->blueColorMappedTexture_, 2, 1);
            connect(this->blueColorMappedTexture_, &TexturePicker::done, [this]() {
                this->heapmapDefinictions_.insert(HeapMapColor::Blue, QImage(*this->blueColorMappedTexture_->image()));
                if(this->heapmapDefinictions_.size() >= 4 && heapmapImage_)
                    emit done(this->heapmapDefinictions_, QImage(*heapmapImage_));
            });

            this->alphaColorLabel_ = new ColorizedLabel("transparent", this);
            this->heapmapDefinitionLayout_->addWidget(this->alphaColorLabel_, 3, 0);
            this->alphaColorMappedTexture_ = new TexturePicker(this);
            this->heapmapDefinitionLayout_->addWidget(this->alphaColorMappedTexture_, 3, 1);
            connect(this->alphaColorMappedTexture_, &TexturePicker::done, [this]() {
                this->heapmapDefinictions_.insert(HeapMapColor::Alpha, QImage(*this->alphaColorMappedTexture_->image()));
                if(this->heapmapDefinictions_.size() >= 4 && heapmapImage_)
                    emit done(this->heapmapDefinictions_, QImage(*heapmapImage_));
            });
        }

        ~HeapmapCreatorSecondStep()
        {
            delete heapmapTexture_;
            delete redColorLabel_;
            delete redColorMappedTexture_;
            delete greenColorLabel_;
            delete greenColorMappedTexture_;
            delete blueColorLabel_;
            delete blueColorMappedTexture_;
            delete alphaColorLabel_;
            delete alphaColorMappedTexture_;
            delete heapmapDefinitionLayout_;
        }

        void load(QImage _heightmap)
        {
            delete heapmapImage_;

            this->heapmapImage_ = new QImage(toControlMap(_heightmap));
            this->heapmapTexture_->setPixmap(QPixmap::fromImage(*this->heapmapImage_).scaled(80, 80, Qt::KeepAspectRatio));
        }

    signals:
        void done(QMap<HeapMapColor, QImage> _heapmapDefinictions, QImage _heapmap);

    private:
        QImage toControlMap(QImage _in)
        {
            const int height = _in.height();
            const int width = _in.width();

            QImage result(width, height, QImage::Format_RGB32);
            unsigned char* resultPtr = result.bits();

            unsigned char* ptr = _in.bits();
            for(int y = 0; y < height; y++)
            {
                for(int x = 0; x < width; x++)
                {
                    int b = ptr[width * 4 * y + 4 * x];
                    int g = ptr[width * 4 * y + 4 * x + 1];
                    int r = ptr[width * 4 * y + 4 * x + 2];
                    int a = ptr[width * 4 * y + 4 * x + 3];

                    float value = r;
                    Color c = heapmap(0.0f, 255.0f, value);

                    resultPtr[width * 4 * y + 4 * x] = c.b;
                    resultPtr[width * 4 * y + 4 * x + 1] = c.g;
                    resultPtr[width * 4 * y + 4 * x + 2] = c.r;
                    resultPtr[width * 4 * y + 4 * x + 3] = a;
                }
            }

            return result;
        }

        Color heapmap(float min, float max, float value)
        {
            float ratio = 2 * (value - min) / (max - min);
            float r = std::max(0.0f, 255 * (ratio - 1));
            float b = std::max(0.0f, 255 * (1 - ratio));
            float g = 255.0f - b - r;
            return Color(r, g, b);
        }

        QMap<HeapMapColor, QImage> heapmapDefinictions_;

        QLabel* heapmapTexture_;
        QImage* heapmapImage_;
        QSpacerItem *leftSpacerItem_, *rightSpacerItem_;

        QGridLayout* heapmapDefinitionLayout_;

        ColorizedLabel* redColorLabel_;
        TexturePicker* redColorMappedTexture_;

        ColorizedLabel* greenColorLabel_;
        TexturePicker* greenColorMappedTexture_;

        ColorizedLabel* blueColorLabel_;
        TexturePicker* blueColorMappedTexture_;

        ColorizedLabel* alphaColorLabel_;
        TexturePicker* alphaColorMappedTexture_;
    };

    class HeapmapCreator
        : public Dialog
    {
        Q_OBJECT

    public:
        explicit HeapmapCreator(QWidget* _parent = nullptr);
        ~HeapmapCreator();

    signals:
        void heapmapCreated(QMap<HeapMapColor, QImage> _heapmapDefinictions, QImage _heapmap);

    private:
        void setupUi() override;

        QImage heapmapImage_;
        QMap<HeapMapColor, QImage> heapmapDefinictions_;

        QVBoxLayout* layout_;
        HeapmapCreatorFirstStep* firstStep_;
        HeapmapCreatorSecondStep* secondStep_;
        TexturePickerDialogButtonsArea* buttonsArea_;
    };
}

#endif // QNAGE_WIDGET_MATERIAL_HEAMPMAP_HEAPMAPCREATOR_H_
