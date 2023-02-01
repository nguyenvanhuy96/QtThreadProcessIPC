#include "consumer.h"

Consumer::Consumer(QObject *parent) : QObject(parent)
{
    m_counter=0;
}
void Consumer::data(const CustomData &cd){
    qDebug() << "Consumer message : " << cd.m_integer << *cd.m_pointer << cd.m_string << " Thread: " << QThread::currentThread();
    // skill the thread
    if(++m_counter >10){
        qDebug() << "Consumer, thread about to be skilled";
        thread()->quit();
    }
}
