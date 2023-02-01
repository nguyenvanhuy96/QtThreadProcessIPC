#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
   qDebug() << "Main thread: " << QThread::currentThread() << ", Id thread: " << QThread::currentThreadId();
}
void Widget::counting(int value){
    for (int i{0};i<value; i++) {
        qDebug() << "Counting: " << i  << ",Running in thread: " << QThread::currentThread() << ", Id thread: " << QThread::currentThreadId();
    }
}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnStart_clicked()
{

    thread = QThread::create([=]{counting(10);}); // old not working:   thread = QThread::create(counting,10);

    connect(thread, &QThread::started,[](){
       qDebug() << "Start thread: " << QThread::currentThread() << " - Id: " << QThread::currentThreadId();
    });
    connect(thread, &QThread::finished,[](){
       qDebug() << "Finished thread: " << QThread::currentThread() << " - Id: " << QThread::currentThreadId();
    });
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}
