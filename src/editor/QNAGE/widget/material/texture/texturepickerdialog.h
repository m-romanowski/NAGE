#ifndef QNAGE_UI_TEXTUREPICKERDIALOG_H_
#define QNAGE_UI_TEXTUREPICKERDIALOG_H_

#include "editor/QNAGE/dialog/dialog.h"
#include "texturepickerdialogstepheader.h"
#include "texturepickerdialogbuttonsarea.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QScreen>
#include <QScroller>
#include <QTreeView>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>

namespace mr::qnage
{
    class FirstStep
        : public QWidget
    {
        Q_OBJECT

    public:
        struct Properties
        {
            QString rootPath;
            QString defaultPath;
            QStringList fileFilters;
            bool useCustomDirectoryIcons;
            bool dontWatchForChanges;
            bool animated;
            bool sorted;

            Properties()
            {
                this->rootPath = "/";
                this->defaultPath = "/";
                this->fileFilters = QStringList();
                this->useCustomDirectoryIcons = false;
                this->dontWatchForChanges = true;
                this->animated = true;
                this->sorted = true;
            }
        };

        explicit FirstStep(const Properties _properties = Properties(), QWidget* _parent = nullptr)
            : QWidget(_parent),
              properties_(_properties)
        {
            this->layout_ = new QVBoxLayout(this);

            this->firstStepLabel_ = new TexturePickerDialogStepHeader("Choose image file", this);
            this->layout_->addWidget(this->firstStepLabel_);

            this->fileSystemModel_ = setupModel(_properties);
            this->fileSystemView_ = setupView(_properties, this->fileSystemModel_);
            this->layout_->addWidget(this->fileSystemView_);

            this->chosedFileName_ = new QLineEdit(this);
            this->chosedFileName_->setEnabled(false);
            this->chosedFileName_->setContentsMargins(0, 20, 0, 0);
            this->layout_->addWidget(this->chosedFileName_);

            this->buttonsArea_ = new TexturePickerDialogButtonsArea("Cancel", "Next step", this);
            this->layout_->addWidget(this->buttonsArea_);
            connect(this->buttonsArea_, &TexturePickerDialogButtonsArea::firstButtonClicked, this, &FirstStep::closeDialogClicked);
            connect(this->buttonsArea_, &TexturePickerDialogButtonsArea::secondButonClicked, this, &FirstStep::nextStepClicked);

            this->setLayout(this->layout_);
            QScroller::grabGesture(this->fileSystemView_, QScroller::TouchGesture);
        }

        ~FirstStep()
        {
            delete firstStepLabel_;
            delete fileSystemModel_;
            delete fileSystemView_;
            delete chosedFileName_;
            delete buttonsArea_;
            delete layout_;
        }

        QString selectedFilePath() const
        {
            return this->chosedFileName_->text();
        }

    signals:
        void nextStepClicked(bool _checked);
        void closeDialogClicked(bool _checked);

    private:
        QFileSystemModel* setupModel(Properties _properties)
        {
            QFileSystemModel* fileSystemModel = new QFileSystemModel;
            fileSystemModel->setRootPath(_properties.rootPath);
            fileSystemModel->setReadOnly(true);
            fileSystemModel->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);

            fileSystemModel->setNameFilters(_properties.fileFilters);
            fileSystemModel->setNameFilterDisables(false);

            if(_properties.useCustomDirectoryIcons)
                fileSystemModel->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);

            if(_properties.dontWatchForChanges)
                fileSystemModel->setOption(QFileSystemModel::DontWatchForChanges);

            return fileSystemModel;
        }

        QTreeView* setupView(Properties _properties, QFileSystemModel* _model)
        {
            QTreeView* view = new QTreeView;
            view->setAnimated(_properties.animated);
            view->setSortingEnabled(_properties.sorted);
            view->setItemsExpandable(true);

            const QSize availableSize = view->screen()->availableGeometry().size();
            view->resize(availableSize / 2);
            view->setColumnWidth(0, view->width() / 3);

            view->setModel(_model);
            QModelIndex idx = _model->index(_properties.defaultPath);
            view->setRootIndex(idx);

            connect(view, &QTreeView::clicked, this, &FirstStep::fileSelected);

            return view;
        }

        void fileSelected(const QModelIndex& _index)
        {
            QString selectedFile = this->fileSystemView_->model()->data(_index).toString();
            for(auto ext : properties_.fileFilters)
            {
                QString fileExtensionWithoutSpecialCharacters = ext.remove(QRegularExpression("[\\!\\@\\#\\$\\%\\^\\&\\*\\(\\)\\~\\`]+"));
                if(selectedFile.endsWith(fileExtensionWithoutSpecialCharacters))
                {
                    QString selectedFileFullPath = this->fileSystemModel_->filePath(_index);
                    this->chosedFileName_->setText(selectedFileFullPath);
                    this->buttonsArea_->enableSecond();
                    return;
                }
            }

            this->chosedFileName_->setText("");
            this->buttonsArea_->disableSecond();
        }

        Properties properties_;

        QVBoxLayout* layout_;
        TexturePickerDialogStepHeader* firstStepLabel_;
        QFileSystemModel* fileSystemModel_;
        QTreeView* fileSystemView_;
        QLineEdit* chosedFileName_;
        TexturePickerDialogButtonsArea* buttonsArea_;
    };
    
    class SecondStep
        : public QWidget
    {
        Q_OBJECT

    public:
        explicit SecondStep(QWidget* _parent = nullptr)
            : QWidget(_parent)
        {
            this->layout_ = new QVBoxLayout;
            this->layout_->setContentsMargins(0, 20, 0, 0);

            this->secondStepLabel_ = new TexturePickerDialogStepHeader("Chosed image", this);
            this->layout_->addWidget(this->secondStepLabel_);

            this->imagePreviewLayout_ = new QHBoxLayout;
            this->imagePreviewLayout_->setSizeConstraint(QLayout::SetMinimumSize);
            this->layout_->addLayout(this->imagePreviewLayout_);
            this->imagePreviewLeftSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            this->imagePreviewLayout_->addItem(imagePreviewLeftSpacerItem_);

            this->previewImageLabel_ = new QLabel(this);
            this->previewImageLabel_->setMinimumSize(200, 200);
            this->previewImageLabel_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
            this->imagePreviewLayout_->addWidget(this->previewImageLabel_);

            this->imagePreviewRightSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            this->imagePreviewLayout_->addItem(this->imagePreviewRightSpacerItem_);

            this->buttonsArea_ = new TexturePickerDialogButtonsArea("Previous step", "Choose", this);
            this->layout_->addWidget(this->buttonsArea_);
            connect(this->buttonsArea_, &TexturePickerDialogButtonsArea::firstButtonClicked, this, &SecondStep::previousStepClicked);
            connect(this->buttonsArea_, &TexturePickerDialogButtonsArea::secondButonClicked, [this] {
                emit chooseClicked(this->textureImage_);
            });

            this->setLayout(this->layout_);
        }

        ~SecondStep()
        {
            delete secondStepLabel_;
            delete imagePreviewLeftSpacerItem_, *imagePreviewRightSpacerItem_;
            delete previewImageLabel_;
            delete imagePreviewLayout_;
            delete buttonsArea_;
            delete layout_;
        }

        void loadImage(QString _imagePath)
        {
            this->textureImage_ = QImage(_imagePath);
            updatePreview();
        }

    signals:
        void previousStepClicked(bool _checked);
        void chooseClicked(QImage image);

    protected slots:
        void resizeEvent(QResizeEvent* _event) override
        {
            QWidget::resizeEvent(_event);

            if(!textureImage_.isNull())
                updatePreview();
        }

    private:
        void updatePreview()
        {
            const QSize previewAreaSize = this->previewImageLabel_->size() * 1.5;
            this->previewImageLabel_->setPixmap(QPixmap::fromImage(this->textureImage_).scaled(previewAreaSize, Qt::KeepAspectRatio));
        }

        QImage textureImage_;

        QVBoxLayout* layout_;
        TexturePickerDialogStepHeader* secondStepLabel_;
        QHBoxLayout* imagePreviewLayout_;
        QSpacerItem *imagePreviewLeftSpacerItem_, *imagePreviewRightSpacerItem_;
        QLabel* previewImageLabel_;
        TexturePickerDialogButtonsArea* buttonsArea_;
    };

    class TexturePickerDialog
        : public Dialog
    {
        Q_OBJECT

    public:
        explicit TexturePickerDialog(QWidget* _parent = nullptr);
        ~TexturePickerDialog();

    signals:
        void textureSelected(QImage _image);

    protected:
        void gotoFirstStep();
        void gotoSecondStep();
        QLayout* mainLayout();

    private:
        void setupUi() override;
        void closeEvent(QCloseEvent* _event) override;

        QVBoxLayout* mainLayout_;
        FirstStep* firstStep_;
        SecondStep* secondStep_;
    };
}

#endif // QNAGE_UI_TEXTUREPICKERDIALOG_H_
