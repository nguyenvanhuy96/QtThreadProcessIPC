#include "printworker.h"

PrintWorker::PrintWorker(QString name, bool * stop, QMutex * mutex,QObject *parent)
    : QThread(parent), m_name(name), m_stop(stop), m_mutex(mutex)
{
    qDebug() << "GUI(Constructor PrintWorker) :" << thread();
    qDebug() << "Thread(Constructor PrintWorker) :" << QThread::currentThread();
}

PrintWorker::~PrintWorker()
{
    qDebug() << "GUI(Deconstructor PrintWorker) :" << thread();
    qDebug() << "Thread(Deconstructor PrintWorker) :" << QThread::currentThread();
}

void PrintWorker::run()
{
    while(!(*m_stop)){
        QMutexLocker lock(m_mutex);
        qDebug() << m_name << ": Thread " << QThread::currentThread();
        qDebug() << m_name << " 1/3:loading ....";
        qDebug() << m_name << " 2/3:loading ....";
        qDebug() << m_name << " 3/3:loading ....";
        sleep(1);
    }
}
