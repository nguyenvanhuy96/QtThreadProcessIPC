#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent)
{
    qDebug() << "GUI(Constructor WorkerThread): " << thread();
    qDebug() << "Thread(Constructor WorkerThread): " << QThread::currentThread();
}

WorkerThread::~WorkerThread()
{
    qDebug() << "GUI(Destroy WorkerThread): " << thread();
    qDebug() << "Thread(Destroy WorkerThread): " << QThread::currentThread();

}

void WorkerThread::run()
{
    for(int i{0}; i <11; i++){
        double percentage = (i/10.0) *100.0;
        // Chú ý: không nên emit quá nhiều lần để cập nhật UI => UI xử lý chậm
        // Để khắc phục tình trạng này, ta hạn chế đẩy dữ liệu để cập nhật UI
        qDebug() << "   === ";
        qDebug() << "   Percentage :" <<percentage << ", Current thread: "<< QThread::currentThread();
        qDebug() << "   GUI(doCounting Worker): " << thread();
        qDebug() << "   Thread(doCounting Worker): " << QThread::currentThread();
        /*
        if (i%1000==0){
           emit currentCount(QVariant::fromValue(percentage).toInt());
         }
         */
        emit currentCount(QVariant::fromValue(percentage).toInt());
    }
    emit countDone();
}

