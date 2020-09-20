#include "threadlogstream.h"

namespace QNAGE
{
    ThreadLogStream::ThreadLogStream(std::ostream& _stream, QObject* _parent)
        : QObject(_parent),
          stream_(_stream)
    {
        oldBuf_ = _stream.rdbuf();
        _stream.rdbuf(this);
    }

    ThreadLogStream::~ThreadLogStream()
    {
        if(!string_.empty())
            emit sendLogString(QString::fromStdString(string_));

        stream_.rdbuf(oldBuf_);
    }
}
