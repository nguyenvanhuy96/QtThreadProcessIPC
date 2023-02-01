#include "worker.h"

Worker::Worker()
{
    qDebug() << "Thread(Constructor Worker): " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "Thread(Destroy Worker): " << QThread::currentThread();
}
void Worker::run()
{
    for(int i{0}; i <11; i++){
        double percentage = (i/10.0) *100.0;
        // Chú ý: không nên emit quá nhiều lần để cập nhật UI => UI xử lý chậm
        // Để khắc phục tình trạng này, ta hạn chế đẩy dữ liệu để cập nhật UI
        qDebug() << "   === ";
        qDebug() << "   Percentage :" <<percentage << ", Current thread: "<< QThread::currentThread();
        qDebug() << "   Thread(doCounting Worker): " << QThread::currentThread();
        /*
        if (i%1000==0){
           emit currentCount(QVariant::fromValue(percentage).toInt());
         }
         emit currentCount(QVariant::fromValue(percentage).toInt());
         */
    }
    //emit countDone();
}
