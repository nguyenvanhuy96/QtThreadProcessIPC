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
// Muốn chạy đoạn code này trong 1 luồng thì gán sự kiện QThread::Started cho phương thức này
void Worker::doCounting()
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
