#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    thread= new WorkerThread(this);
    connect(thread, &QThread::started,[](){
        qDebug() << "Started thread: " << QThread::currentThread();
    });
    connect(thread, &QThread::finished,[](){
        qDebug() << "Finished thread: " << QThread::currentThread();
    });
}

Widget::~Widget()
{
    delete ui;
    thread->quit();
}


void Widget::on_btnStart_clicked()
{
    thread->start();
}

void Widget::on_btnStop_clicked()
{

}

void Widget::on_btnInfo_clicked()
{
    qDebug() << "Thread is running: " << thread->isRunning();
}
