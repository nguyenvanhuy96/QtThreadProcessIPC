#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "GUI(Constructor Widget): " << thread();
    qDebug() << "Thread(Constructor Widget): " << QThread::currentThread();

    workerThread = new QThread(this);

    connect(workerThread, &QThread::started, [](){
        qDebug() << "   (workerThread Started) " ;
    });
    connect(workerThread, &QThread::finished, [](){
        qDebug() << "   (workerThread Finised) " ;
    });
    connect(workerThread, &QThread::finished, this, &Widget::threadFinished);

}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_btnStart_clicked()
{
    Worker *worker = new Worker;
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::started,worker, &Worker::doCounting); // Phương thức doCounting tách riêng ra một thread khác.
    connect(worker, &Worker::currentCount, this, &Widget::currentCount);
    connect(worker, &Worker::countDone, this, &Widget::countDone);
    connect(workerThread, &QThread::finished, worker, &Worker::deleteLater);
    workerThread->start();
}

void Widget::on_btnInfo_clicked()
{
    qDebug() << "--------Info--------";
    qDebug() << "        GUI(on_btnInfo_clicked): " << thread();
    qDebug() << "        WorkerThread(on_btnInfo_clicked): " << workerThread->isRunning();
    qDebug() << "        Thread(on_btnInfo_clicked): " << QThread::currentThread();
}

void Widget::countDone()
{
    qDebug() << "GUI(countDone): " << thread();
    qDebug() << "Thread(countDone): " << QThread::currentThread();
    workerThread->exit();
    qDebug() << "Exited thread workerThread(countDone): " << workerThread->isRunning();
}
void Widget::currentCount(int value)
{
    ui->pgb->setValue(value);
    ui->lb->setText(QString::number(value));
}

void Widget::threadFinished()
{
    qDebug() << "GUID(threadFinished): " << thread();
    qDebug() << "Thread(threadFinished): " << QThread::currentThread();
}
