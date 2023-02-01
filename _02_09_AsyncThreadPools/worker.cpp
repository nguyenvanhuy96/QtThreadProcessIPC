#include "worker.h"

Worker::Worker(QObject *receiver):m_receiver(receiver)

{
    qDebug() << "Thread(Constructor Worker): " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "Thread(Destroy Worker): " << QThread::currentThread();
}
void Worker::run()
{
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [](){
       qDebug() << "Time out running in thread: " << QThread::currentThread();
    });
    timer->setInterval(1);
    timer->start();
}
