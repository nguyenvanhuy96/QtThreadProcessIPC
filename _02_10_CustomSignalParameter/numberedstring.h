#ifndef NUMBEREDSTRING_H
#define NUMBEREDSTRING_H

#include <QString>
#include <QMetaType>

class NumberedString
{
public:
    NumberedString(int number, QString string);
    int number() const;
    QString string() const;
private:
    int m_number;
    QString m_string;
};
Q_DECLARE_METATYPE(NumberedString);

#endif // NUMBEREDSTRING_H
