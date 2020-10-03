#include "logwidget.h"

namespace mr::qnage
{
    LogWidget::LogWidget(QWidget* _parent)
        : QWidget(_parent),
          msgHandler_(nullptr)
    {
        setupUi();

        // Redirect IO output to QPlainTextEdit
        logStream_ = new ThreadLogStream(std::cout);
        this->msgHandler_ = new MessageHandler(debugIO_, this);
        connect(logStream_, &ThreadLogStream::sendLogString, msgHandler_, &MessageHandler::catchMessage);
    }

    LogWidget::~LogWidget()
    {
        delete msgHandler_;
        delete logStream_;
        delete clearButton_;
        delete debugIO_;
        delete optLayout_;
        delete mainLayout_;
    }

    void LogWidget::setupUi()
    {
        // Main layout
        mainLayout_ = new QVBoxLayout(this);

        // Options layout
        optLayout_ = new QGridLayout();
        optLayout_->setAlignment(Qt::AlignLeft);

        // Clear button
        this->clearButton_ = new QPushButton();
        this->clearButton_->setObjectName("dark-btn");
        this->clearButton_->setToolTip(tr("Clear debug console"));
        this->clearButton_->setMinimumSize(QSize(60, 30));
        this->clearButton_->setMaximumSize(QSize(60, 30));
        this->clearButton_->setText("");
        QIcon exitButtonIcon = QIcon();
        exitButtonIcon.addPixmap(QPixmap(":/rc/icons/clear-terminal.png"), QIcon::Normal, QIcon::Off);
        this->clearButton_->setIcon(exitButtonIcon);
        this->clearButton_->setIconSize(QSize(23, 23));
        this->clearButton_->setProperty("class", "window-button");
        this->clearButton_->setStyleSheet("QPushButton { border: none; }");
        connect(this->clearButton_, &QPushButton::clicked, this, [this]{ this->onClearButtonClicked(); });
        this->optLayout_->addWidget(this->clearButton_, 0, 0, 0, 0);

        // Debug IO
        this->debugIO_ = new QPlainTextEdit();
        this->debugIO_->setReadOnly(true);
        connect(this->debugIO_, &QPlainTextEdit::textChanged, this, &LogWidget::onDebugIOChange);

        // Bind layouts
        this->mainLayout_->addLayout(optLayout_);
        this->mainLayout_->addWidget(debugIO_);
    }

    void LogWidget::onClearButtonClicked()
    {
        this->debugIO_->clear();
    }

    void LogWidget::onDebugIOChange()
    {
        // Move scrollbar to bottom.
        this->debugIO_->verticalScrollBar()->setValue(this->debugIO_->verticalScrollBar()->maximum());
    }

    void LogWidget::QMessageOutput(QtMsgType _type, const QMessageLogContext& _context, const QString& _msg)
    {
        Q_UNUSED(_type);
        Q_UNUSED(_context);

        std::cout << _msg.toStdString().c_str() << std::endl;
    }
}
