#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "GUI thread: " << QThread::currentThread();

    connect(&watcher, &QFutureWatcher<void>::finished,[=](){
        qDebug() << "---Computation done";

        if(!watcher.isCanceled()){
            QVector<int> resultVector = watcher.result();
            qDebug() << "Number of items in resultVector: " << resultVector.count();


            for (int i{0};i<resultVector.count();i++) {
                qDebug() << "Element [" << i << "]: " << resultVector[i];
            }
        }else{
            qDebug() << "Watcher already cancelled!";
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

QFuture<QVector<int> > Widget::heavyWorkWithReturn()
{
    auto heavyWork = [=](){
        QVector<int> intVector;
        for (int i{0};i<1000000001; i++) {
            if ((i%100000) ==0){
                double percentage = ((i/1000000000.0))*100;
                intVector.push_back(QVariant::fromValue(percentage).toInt());
            }
        }
        return  intVector;
    };
    return QtConcurrent::run(heavyWork);
}


void Widget::on_btnStart_clicked()
{
    future = heavyWorkWithReturn();
    watcher.setFuture(future);
}

void Widget::on_btnCancel_clicked()
{
    watcher.cancel();
}

void Widget::on_btnPause_clicked()
{
    watcher.pause();
}

void Widget::on_btnResume_clicked()
{
    watcher.resume();
}
