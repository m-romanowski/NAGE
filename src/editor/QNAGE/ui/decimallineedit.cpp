#include "decimallineedit.h"

#include <QDebug>

namespace mr::qnage
{
    DecimalLineEdit::DecimalLineEdit(const QString _label, QWidget* _parent)
        : QLineEdit(_parent),
          label_(_label)
    {
        this->setText(optLabel() + "0");
        this->setPlaceholderText(optLabel() + "0");
        this->setValidator(new QRegExpValidator(QRegExp(VALIDATION_REGEX)));

        connect(this, &QLineEdit::editingFinished, [this]() {
            auto prevValue = this->text();
            this->setText(optLabel() + prevValue);
        });
    }

    void DecimalLineEdit::focusInEvent(QFocusEvent* _event)
    {
        QLineEdit::focusInEvent(_event);
        this->focused_ = true;
    }

    void DecimalLineEdit::focusOutEvent(QFocusEvent* _event)
    {
        QLineEdit::focusOutEvent(_event);
        this->focused_ = false;
    }

    void DecimalLineEdit::wheelEvent(QWheelEvent* _event)
    {
        QLineEdit::wheelEvent(_event);
        if(this->focused_)
        {
            int delta = _event->angleDelta().y() > 0
                ? 1
                : -1;

            auto prevValue = extractNumber();
            this->setText(optLabel() + QString::number(prevValue + delta));
        }
    }

    int DecimalLineEdit::value() const
    {
        return this->text().toInt();
    }

    QString DecimalLineEdit::optLabel() const
    {
        return !this->label_.isEmpty()
            ? this->label_ + OPTIONAL_LABEL_DELIM + " "
            : "";
    }

    int DecimalLineEdit::extractNumber() const
    {
        QRegExp regex("([-]?\\d+)(?:\\s*)");
        QStringList numberList;

        int pos = 0;
        while((pos = regex.indexIn(this->text(), pos)) != -1)
        {
            numberList << regex.cap(1);
            pos += regex.matchedLength();
        }

        if(numberList.size() > 1 || numberList.size() < 1)
            throw new std::invalid_argument("Unexpected error while parsing input, reason: expect one number");

        return numberList.at(0).toInt();
    }
}
