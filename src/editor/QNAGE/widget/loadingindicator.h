#ifndef QNAGE_WIDGET_LOADINGINDICATOR_H_
#define QNAGE_WIDGET_LOADINGINDICATOR_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QMovie>
#include <QSpacerItem>
#include <QLabel>

namespace mr::qnage
{
    class LoadingIndicator
        : public QWidget
    {
        inline static const QSize INDICATOR_SIZE = QSize(80, 80);

    public:
        explicit LoadingIndicator(QWidget* _parent = nullptr)
            : QWidget(_parent)
        {
            this->setStyleSheet("QWidget { background-color: #e5eff1; }");

            this->mainLayout_ = new QVBoxLayout;
            this->mainLayout_->setSpacing(0);
            this->mainLayout_->setContentsMargins(0, 0, 0, 0);
            this->setLayout(this->mainLayout_);

            this->vSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
            this->mainLayout_->addItem(this->vSpacerItem_);

            this->bottomLayout_ = new QHBoxLayout;
            this->bottomLayout_->setSpacing(0);
            this->bottomLayout_->setContentsMargins(0, 0, 20, 20);
            this->mainLayout_->addLayout(this->bottomLayout_);

            this->hSpacerItem_ = new QSpacerItem(1, 1, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
            this->bottomLayout_->addItem(this->hSpacerItem_);

            this->indicatorLabel_ = new QLabel;
            this->indicatorLabel_->setFixedSize(INDICATOR_SIZE);
            this->indicatorLoaderAnimation_ = new QMovie(":/rc/icons/animated/spinningwheel.gif");
            this->indicatorLoaderAnimation_->setScaledSize(INDICATOR_SIZE);
            this->indicatorLabel_->setMovie(this->indicatorLoaderAnimation_);
            this->bottomLayout_->addWidget(this->indicatorLabel_, Qt::AlignRight | Qt::AlignBottom);
        }

        ~LoadingIndicator()
        {
            delete bottomLayout_;
            delete hSpacerItem_;
            delete indicatorLoaderAnimation_;
            delete indicatorLabel_;
            delete vSpacerItem_;
            delete mainLayout_;
        }

        void start()
        {
            this->show();
            this->indicatorLoaderAnimation_->start();
        }

        void stop()
        {
            this->hide();
            this->indicatorLoaderAnimation_->stop();
        }

    private:
        QVBoxLayout* mainLayout_;
        QSpacerItem* vSpacerItem_;
        QHBoxLayout* bottomLayout_;
        QSpacerItem* hSpacerItem_;
        QLabel* indicatorLabel_;
        QMovie* indicatorLoaderAnimation_;
    };
}

#endif // QNAGE_WIDGET_LOADINGINDICATOR_H_
