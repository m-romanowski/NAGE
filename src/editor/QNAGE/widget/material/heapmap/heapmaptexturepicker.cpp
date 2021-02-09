#include "heapmaptexturepicker.h"

namespace mr::qnage
{
    HeapmapTexturePicker::HeapmapTexturePicker(QWidget* _parent, QSize _pickerAreaSize)
        : BaseTexturePicker(_parent, _pickerAreaSize)
    {
        this->dialog_ = std::make_unique<HeapmapCreator>();
        connect(reinterpret_cast<HeapmapCreator*>(this->dialog_.get()), &HeapmapCreator::heapmapCreated,
            [this](QMap<HeapMapColor, QImage> _heapmapDefinitions, QImage _heapmap) {
                delete texture_;
                this->texture_ = new QImage(_heapmap);
                this->setPixmap(QPixmap::fromImage(*texture_).scaled(this->pickerAreaSize_));
                this->heapmapDefinitions_ = _heapmapDefinitions;

                emit done(QImage(*this->texture_));
                this->dialog_->close();
        });
    }

    QMap<HeapMapColor, QImage> HeapmapTexturePicker::heapmapDefinition() const
    {
        return heapmapDefinitions_;
    }
}
