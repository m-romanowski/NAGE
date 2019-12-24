#include "threadlogstream.h"

namespace QNAGE
{
    ThreadLogStream::ThreadLogStream(std::ostream& _stream, QObject* _parent)
        : QObject(_parent),
          stream(_stream)
    {
        oldBuf = _stream.rdbuf();
        _stream.rdbuf(this);
    }

    ThreadLogStream::~ThreadLogStream()
    {
        if(!string.empty())
            emit sendLogString(QString::fromStdString(string));

        stream.rdbuf(oldBuf);
    }
}
