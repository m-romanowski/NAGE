#include "messagehandler.h"

namespace QNAGE
{
    MessageHandler::MessageHandler(QPlainTextEdit* _textEdit, QObject* _parent)
        : QObject(_parent),
          textEdit_(_textEdit)
    {

    }

    void MessageHandler::catchMessage(QString _msg)
    {
        this->textEdit_->appendPlainText(_msg);
    }
}
