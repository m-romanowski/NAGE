#ifndef QNAGE_DEBUGGER_THREADLOGSTREAM_H_
#define QNAGE_DEBUGGER_THREADLOGSTREAM_H_

#include <QObject>

#include <iostream>
#include <streambuf>
#include <string>

namespace QNAGE
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
                emit sendLogString(QString::fromStdString(string));
                string.erase(string.begin(), string.end());
            }
            else
            {
                string += static_cast<char>(_v);
            }

            return _v;
        }

        virtual std::streamsize xsputn(const char* _p, std::streamsize _n)
        {
            string.append(_p, _p + _n);
            long pos = 0;

            while(pos != static_cast<long>(std::string::npos))
            {
                pos = static_cast<long>(string.find('\n'));
                if(pos != static_cast<long>(std::string::npos))
                {
                    std::string tmp(string.begin(), string.begin() + pos);
                    emit sendLogString(QString::fromStdString(tmp));
                    string.erase(string.begin(), string.begin() + pos + 1);
                }
            }

            return _n;
        }

    private:
        std::ostream& stream;
        std::streambuf* oldBuf;
        std::string string;

    signals:
        void sendLogString(const QString& _str);
    };
}

#endif // QNAGE_DEBUGGER_THREADLOGSTREAM_H_
