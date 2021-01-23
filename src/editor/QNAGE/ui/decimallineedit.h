#ifndef QNAGE_UI_DECIMALLINEEDIT_H_
#define QNAGE_UI_DECIMALLINEEDIT_H_

#include <QLineEdit>
#include <QFocusEvent>
#include <QWheelEvent>
#include <QRegExpValidator>

namespace mr::qnage
{
    class DecimalLineEdit
        : public QLineEdit
    {
        Q_OBJECT

        inline static const QString OPTIONAL_LABEL_DELIM = ":";
        inline static const QString VALIDATION_REGEX = "([a-zA-Z]+:[ ])?([-]?[0-9]+)";

    public:
        DecimalLineEdit(const QString _label = "", QWidget* _parent = nullptr);

        void set(int _value);
        int value() const;

    protected:
        void focusInEvent(QFocusEvent* _event) override;
        void focusOutEvent(QFocusEvent* _event) override;
        void wheelEvent(QWheelEvent* _event) override;

    private:
        QString optLabel() const;
        int extractNumber() const;
        void update(int newValue);

        bool focused_;
        QString label_;
    };
}

#endif // QNAGE_UI_DECIMALLINEEDIT_H_
