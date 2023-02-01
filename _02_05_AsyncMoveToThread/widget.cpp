#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "Thread (Constructor widget): " << QThread::currentThread();
    workerThread = new QThread(this);
}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
  Worker * worker = new Worker;
  worker->moveToThread(workerThread);

  connect(workerThread, &QThread::started, worker, &Worker::doWork);
  connect(workerThread, &QThread::finished,[](){
      qDebug() << "Thread finished: " << QThread::currentThread();
  });
  connect(workerThread, &QThread::finished,&QThread::deleteLater);
  workerThread->start();
}

void Widget::on_btnStop_clicked()
{
  workerThread->exit();
}

void Widget::on_btnInfo_clicked()
{
  qDebug() << "Worker thread is running: " << workerThread->isRunning();
}
