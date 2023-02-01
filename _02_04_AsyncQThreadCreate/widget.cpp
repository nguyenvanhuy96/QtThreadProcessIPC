#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "UI thread: " << QThread::currentThread();
    thread = QThread::create([](){
        QTimer* timer = new QTimer();
        connect(timer, &QTimer::timeout, [](){
            qDebug() << "Time out running in thread: " << QThread::currentThread();
        });
        timer->setInterval(1000);
        timer->start();
    });
    connect(thread, &QThread::started, [](){
        qDebug() << "Thread started running in thread: " << QThread::currentThread();
    });
    connect(thread, &QThread::finished, [](){
        qDebug() << "Thread finished running in thread: " << QThread::currentThread();
    });
    thread->start();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_btnStart_clicked()
{

}
