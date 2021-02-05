#include <QStandardPaths>
#include "texturepickerdialog.h"

namespace mr::qnage
{
    TexturePickerDialog::TexturePickerDialog(QWidget* _parent)
        : Dialog(_parent)
    {
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
        this->setWindowModality(Qt::WindowModal);

        setupUi();
    }

    TexturePickerDialog::~TexturePickerDialog()
    {
        delete firstStep_;
        delete mainLayout_;
    }

    void TexturePickerDialog::setupUi()
    {
        this->mainLayout_ = new QVBoxLayout(this);
        this->setLayout(this->mainLayout_);

        FirstStep::Properties firstStepProperties = FirstStep::Properties();
        firstStepProperties.rootPath = QStandardPaths::HomeLocation;
        this->firstStep_ = new FirstStep(firstStepProperties, this);
        this->mainLayout_->addWidget(this->firstStep_);
    }
}
