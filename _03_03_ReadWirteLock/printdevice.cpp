#include "printdevice.h"

PrintDevice::PrintDevice()
{
    m_count=0;

}
void PrintDevice::print(const QString     &text){
    QReadLocker readLocker(&m_readWirteLock);
    qDebug() << text << "Callled, count: " << m_count;
    qDebug() << text << " 1/3loading.... " ;
    qDebug() << text << " 2/3loading.... " ;
    qDebug() << text << " 3/3loading.... " ;
}
void PrintDevice::increment(){
    QWriteLocker writeLocker(&m_readWirteLock);
    m_count++;
}
