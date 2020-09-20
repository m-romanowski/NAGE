#ifndef QNAGE_DEBUGGER_MESSAGEHANDLER_H_
#define QNAGE_DEBUGGER_MESSAGEHANDLER_H_

#include <QDateTime>
#include <QPlainTextEdit>
#include <QString>

namespace QNAGE
{
    class MessageHandler : public QObject
    {
        Q_OBJECT

    public:
        MessageHandler(QPlainTextEdit* _textEdit, QObject* _parent = nullptr);

    public slots:
        void catchMessage(QString _msg);

    private:
        QPlainTextEdit* textEdit_;
    };
}

#endif // QNAGE_DEBUGGER_MESSAGEHANDLER_H_
