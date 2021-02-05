#ifndef QNAGE_UI_TEXTUREPICKERDIALOG_H_
#define QNAGE_UI_TEXTUREPICKERDIALOG_H_

#include "editor/QNAGE/dialog/dialog.h"

#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QScreen>
#include <QScroller>
#include <QTreeView>

namespace mr::qnage
{
    class TexturePickerDialog
        : public Dialog
    {
    protected:
        class FirstStep
            : public QWidget
        {
        public:
            struct Properties
            {
                QString rootPath;
                bool useCustomDirectoryIcons;
                bool dontWatchForChanges;
                bool animated;
                bool sorted;

                Properties()
                {
                    this->rootPath = "";
                    this->useCustomDirectoryIcons = false;
                    this->dontWatchForChanges = true;
                    this->animated = true;
                    this->sorted = true;
                }
            };

            explicit FirstStep(const Properties _properties = Properties(), QWidget* _parent = nullptr)
                : QWidget(_parent)
            {
                this->layout_ = new QVBoxLayout(this);
                this->setLayout(this->layout_);

                this->fileSystemModel_ = new QFileSystemModel;
                this->fileSystemModel_->setRootPath(_properties.rootPath);
                this->fileSystemModel_->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);

                QStringList supportedExtensions;
                supportedExtensions.append("*.png");
                supportedExtensions.append("*.jpg");
                supportedExtensions.append("*.jpeg");
                supportedExtensions.append("*.bmp");

                this->fileSystemModel_->setNameFilters(supportedExtensions);
                this->fileSystemModel_->setNameFilterDisables(false);

                if(_properties.useCustomDirectoryIcons)
                    this->fileSystemModel_->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);

                if(_properties.dontWatchForChanges)
                    this->fileSystemModel_->setOption(QFileSystemModel::DontWatchForChanges);

                this->fileSystemView_ = new QTreeView;
                this->fileSystemView_->setAnimated(_properties.animated);
                this->fileSystemView_->setSortingEnabled(_properties.sorted);

                const QSize availableSize = this->fileSystemView_->screen()->availableGeometry().size();
                this->fileSystemView_->resize(availableSize / 2);
                this->fileSystemView_->setColumnWidth(0, this->fileSystemView_->width() / 3);

                this->fileSystemView_->setModel(this->fileSystemModel_);
                this->layout_->addWidget(this->fileSystemView_);

                QScroller::grabGesture(this->fileSystemView_, QScroller::TouchGesture);
            }

            ~FirstStep()
            {
                delete fileSystemModel_;
                delete fileSystemView_;
                delete layout_;
            }

        private:
            QVBoxLayout* layout_;
            QFileSystemModel* fileSystemModel_;
            QTreeView* fileSystemView_;
        };

    public:
        explicit TexturePickerDialog(QWidget* _parent = nullptr);
        ~TexturePickerDialog();

    private:
        void setupUi() override;

        QVBoxLayout* mainLayout_;
        FirstStep* firstStep_;
    };
}

#endif // QNAGE_UI_TEXTUREPICKERDIALOG_H_
