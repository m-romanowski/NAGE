#include <QStandardPaths>
#include "texturepickerdialog.h"

namespace mr::qnage
{
    TexturePickerDialog::TexturePickerDialog(QWidget* _parent)
        : Dialog(_parent)
    {
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
        this->setWindowModality(Qt::WindowModal);
        this->setWindowTitle("Texture picker");
        this->setMinimumSize(650, 350);
        this->setMaximumHeight(450);
        this->setContentsMargins(20, 30, 20, 30);

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

        QStringList supportedExtensions;
        supportedExtensions.append("*.png");
        supportedExtensions.append("*.jpg");
        supportedExtensions.append("*.jpeg");
        supportedExtensions.append("*.bmp");

        FirstStep::Properties firstStepProperties = FirstStep::Properties();
        firstStepProperties.rootPath = "/home/inc/terrain";
        firstStepProperties.defaultPath = "/home/inc/terrain";
        // firstStepProperties.rootPath = QStandardPaths::HomeLocation;
        // firstStepProperties.defaultPath = QStandardPaths::HomeLocation; // TODO: fix to QApplication::applicationDirPath()
        firstStepProperties.fileFilters = supportedExtensions;

        this->firstStep_ = new FirstStep(firstStepProperties, this);
        this->mainLayout_->addWidget(this->firstStep_);
        connect(this->firstStep_, &FirstStep::nextStepClicked, [this]{
            this->secondStep_->loadImage(this->firstStep_->selectedFilePath());
            gotoSecondStep();
        });
        connect(this->firstStep_, &FirstStep::closeDialogClicked, [this] {
            gotoFirstStep();
            this->close();
        });

        this->secondStep_ = new SecondStep(this);
        this->mainLayout_->addWidget(this->secondStep_);
        this->secondStep_->hide();
        connect(this->secondStep_, &SecondStep::previousStepClicked, [this]{
            gotoFirstStep();
        });
        connect(this->secondStep_, &SecondStep::chooseClicked, this, [this](QImage _selectedImage) {
            emit textureSelected(_selectedImage);
        });
    }

    QLayout* TexturePickerDialog::mainLayout()
    {
        return this->mainLayout_;
    }

    void TexturePickerDialog::gotoFirstStep()
    {
        if(!this->firstStep_ || !this->secondStep_)
            return;

        this->secondStep_->hide();
        this->firstStep_->show();
    }

    void TexturePickerDialog::gotoSecondStep()
    {
        if(!this->firstStep_ || !this->secondStep_)
            return;

        this->firstStep_->hide();
        this->secondStep_->show();
    }

    void TexturePickerDialog::closeEvent(QCloseEvent* _event)
    {
        gotoFirstStep();
        QWidget::closeEvent(_event);
    }
}
