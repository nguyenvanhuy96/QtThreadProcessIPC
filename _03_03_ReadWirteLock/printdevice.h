#ifndef PRINTDEVICE_H
#define PRINTDEVICE_H

#include <QString>
#include <QReadWriteLock>
#include <QDebug>
class PrintDevice
{
public:
    PrintDevice();
    void print(const QString     &text);
    void increment();
private:
    int m_count;
    QReadWriteLock m_readWirteLock;
};

#endif // PRINTDEVICE_H
