#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    qDebug() << "GUI(Constructor Worker): " << thread();
    qDebug() << "Thread(Constructor Worker): " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "GUI(Destroy Worker): " << thread();
    qDebug() << "Thread(Destroy Worker): " << QThread::currentThread();
}

void Worker::doWork()
{
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, [](){
        qDebug() << "Time out running in thread: " << QThread::currentThread();
    });
    timer->setInterval(1000);
    timer->start();
}
