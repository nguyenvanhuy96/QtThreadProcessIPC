#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent)
{
    qDebug() << "GUI(Constructor WorkerThread): " << thread();
    qDebug() << "Thread(Constructor WorkerThread): " << QThread::currentThread();
}
WorkerThread::~WorkerThread(){
    qDebug() << "GUI(Destroy WorkerThread): " << thread();
    qDebug() << "Thread(Destroy WorkerThread): " << QThread::currentThread();
}

void WorkerThread::run()
{
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, [](){
        qDebug() << "Time out running in thread: " << QThread::currentThread();
    });
    timer->setInterval(1000);
    timer->start();
    exec();
}

