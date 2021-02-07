#include "heapmapcreator.h"

namespace mr::qnage
{
    HeapmapCreator::HeapmapCreator(QWidget* _parent)
        : Dialog(_parent)
    {
        this->setWindowTitle("Heapmap creator");
        this->setFixedWidth(350);

        setupUi();
    }

    HeapmapCreator::~HeapmapCreator()
    {
        delete firstStep_;
        delete secondStep_;
        delete buttonsArea_;
        delete layout_;
    }

    void HeapmapCreator::setupUi()
    {
        this->layout_ = new QVBoxLayout;
        this->setLayout(this->layout_);

        this->firstStep_ = new HeapmapCreatorFirstStep(this);
        this->layout_->addWidget(this->firstStep_);
        connect(this->firstStep_, &HeapmapCreatorFirstStep::imageSelected, [this](QImage _in) {
            this->secondStep_->load(_in);
            this->secondStep_->show();
        });

        this->secondStep_ = new HeapmapCreatorSecondStep(this);
        this->secondStep_->hide();
        this->layout_->addWidget(this->secondStep_);
        connect(this->secondStep_, &HeapmapCreatorSecondStep::done, [this](QMap<HeapMapColor, QImage> _heapmapDefinictions, QImage _heapmap) {
            this->heapmapDefinictions_ = _heapmapDefinictions;
            this->heapmapImage_ = _heapmap;
            this->buttonsArea_->enableSecond();
        });

        this->buttonsArea_ = new TexturePickerDialogButtonsArea("Cancel", "Done", this);
        this->buttonsArea_->disableSecond();
        this->layout_->addWidget(this->buttonsArea_);
        connect(this->buttonsArea_, &TexturePickerDialogButtonsArea::firstButtonClicked, [this]() {
            this->close();
        });
        connect(this->buttonsArea_, &TexturePickerDialogButtonsArea::secondButonClicked, [this]() {
            if(this->heapmapDefinictions_.size() > 0 && !this->heapmapImage_.isNull())
                emit heapmapCreated(this->heapmapDefinictions_, this->heapmapImage_);
        });
    }
}
