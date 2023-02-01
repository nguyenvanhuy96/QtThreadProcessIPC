#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "GUI(Constructor widget): " << thread();
    qDebug() << "Thread(Constructor widget): " << QThread::currentThread();
    workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::currentCount, this, &Widget::currentChanged);
    connect(workerThread, &QThread::started, [](){
        qDebug() << "   (workerThread Started) " ;
    });
    connect(workerThread, &QThread::finished, [](){
        qDebug() << "   (workerThread Finised) " ;
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::currentChanged(int value)
{
    ui->pgb->setValue(value);
    ui->lb->setText(QString::number(value));
}


void Widget::on_btnStart_clicked()
{
    workerThread->start();
}

void Widget::on_btnInfo_clicked()
{
    qDebug() << "   ---Info--- " ;
    qDebug() << "   WorkerThread(Info): " << workerThread->isRunning();
}
