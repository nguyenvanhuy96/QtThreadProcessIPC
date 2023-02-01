#include "printdevice.h"
#include <QMutexLocker>

PrintDevice::PrintDevice()
{
    m_count =0;
}

void PrintDevice::print(const QString &text)
{
   QMutexLocker lock(&m_mutex);
   qDebug() << text << "Called, count: " << m_count++;
   qDebug() << text << " 1/3:loading ....";
   qDebug() << text << " 2/3:loading ....";
   qDebug() << text << " 3/3:loading ....";
}
