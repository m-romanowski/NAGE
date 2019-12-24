#include "logwidget.h"

namespace QNAGE
{
    LogWidget::LogWidget(QWidget* _parent)
        : QWidget(_parent),
          msgHandler(nullptr)
    {
        setupUi();

        // Redirect IO output to QPlainTextEdit
        logStream = new ThreadLogStream(std::cout);
        this->msgHandler = new MessageHandler(debugIO, this);
        connect(logStream, &ThreadLogStream::sendLogString, msgHandler, &MessageHandler::catchMessage);
    }

    LogWidget::~LogWidget()
    {
        delete msgHandler;
        delete logStream;
        delete clearButton;
        delete debugIO;
        delete optLayout;
        delete mainLayout;
    }

    void LogWidget::setupUi()
    {
        // Main layout
        mainLayout = new QVBoxLayout(this);

        // Options layout
        optLayout = new QGridLayout();
        optLayout->setAlignment(Qt::AlignLeft);

        // Clear button
        this->clearButton = new QPushButton();
        this->clearButton->setObjectName("dark-btn");
        this->clearButton->setToolTip(tr("Clear debug console"));
        this->clearButton->setMinimumSize(QSize(60, 30));
        this->clearButton->setMaximumSize(QSize(60, 30));
        this->clearButton->setText("");
        QIcon exitButtonIcon = QIcon();
        exitButtonIcon.addPixmap(QPixmap(":/rc/icons/clear-terminal.png"), QIcon::Normal, QIcon::Off);
        this->clearButton->setIcon(exitButtonIcon);
        this->clearButton->setIconSize(QSize(23, 23));
        this->clearButton->setProperty("class", "window-button");
        this->clearButton->setStyleSheet("QPushButton { border: none; }");
        connect(this->clearButton, &QPushButton::clicked, this, [this]{ this->onClearButtonClicked(); });
        this->optLayout->addWidget(this->clearButton, 0, 0, 0, 0);

        // Debug IO
        this->debugIO = new QPlainTextEdit();
        this->debugIO->setReadOnly(true);
        connect(this->debugIO, &QPlainTextEdit::textChanged, this, &LogWidget::onDebugIOChange);

        // Bind layouts
        this->mainLayout->addLayout(optLayout);
        this->mainLayout->addWidget(debugIO);
    }

    void LogWidget::onClearButtonClicked()
    {
        this->debugIO->clear();
    }

    void LogWidget::onDebugIOChange()
    {
        // Move scrollbar to bottom.
        this->debugIO->verticalScrollBar()->setValue(this->debugIO->verticalScrollBar()->maximum());
    }

    void LogWidget::QMessageOutput(QtMsgType _type, const QMessageLogContext& _context, const QString& _msg)
    {
        Q_UNUSED(_type);
        Q_UNUSED(_context);

        std::cout << _msg.toStdString().c_str() << std::endl;
    }
}
