#ifndef QNAGE_LOG_THREADLOGSTREAM_H_
#define QNAGE_LOG_THREADLOGSTREAM_H_

#include <QObject>

#include <iostream>
#include <streambuf>
#include <string>

namespace mr::qnage
{
    class ThreadLogStream : public QObject, public std::basic_streambuf<char>
    {
        Q_OBJECT

    public:
        ThreadLogStream(std::ostream& _stream, QObject* _parent = nullptr);
        ~ThreadLogStream();

    protected:
        virtual int_type overflow(int_type _v)
        {
            if(_v == '\n')
            {
                emit sendLogString(QString::fromStdString(string_));
                string_.erase(string_.begin(), string_.end());
            }
            else
            {
                string_ += static_cast<char>(_v);
            }

            return _v;
        }

        virtual std::streamsize xsputn(const char* _p, std::streamsize _n)
        {
            string_.append(_p, _p + _n);
            long pos = 0;

            while(pos != static_cast<long>(std::string::npos))
            {
                pos = static_cast<long>(string_.find('\n'));
                if(pos != static_cast<long>(std::string::npos))
                {
                    std::string tmp(string_.begin(), string_.begin() + pos);
                    emit sendLogString(QString::fromStdString(tmp));
                    string_.erase(string_.begin(), string_.begin() + pos + 1);
                }
            }

            return _n;
        }

    private:
        std::ostream& stream_;
        std::streambuf* oldBuf_;
        std::string string_;

    signals:
        void sendLogString(const QString& _str);
    };
}

#endif // QNAGE_LOG_THREADLOGSTREAM_H_
