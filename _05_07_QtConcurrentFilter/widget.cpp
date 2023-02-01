#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "UI thread: " << QThread::currentThread();

    // populate int list with numbers
    for (int i{0};i< 100; i++) {
        inList << QRandomGenerator::global() ->bounded(1000);
    }
    qDebug() << "Before,item count " << inList.count();
    // clear the lists
    ui->lstwSource->clear();
    ui->lstwDes->clear();

    // populate original ui list widget
    foreach (int value, inList) {
        ui->lstwSource->addItem(QString::number(value));
    }
    // minitor work using QFutureWatcher
    connect(&futureWatcher, &QFutureWatcher<void>::started,[=](){
        qDebug() << "asynchronous: Work stared.";
    });
    connect(&futureWatcher, &QFutureWatcher<void>::finished,[=](){
        qDebug() << "asynchronous: Work finished.";
        qDebug() << "Modified list " <<inList;
        ui->lstwDes->clear();
        foreach(int number, inList){
            ui->lstwDes->addItem(QString::number(number));
        }
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnFilter_clicked()
{
    auto filter = [=](const int value){
        if(value >= filterValue){
            qDebug() << "Thread " << QThread::currentThread() << " .Value " <<value;
            return false;
        }
        return  true;
    };

    // clear filtered list
    ui->lstwDes->clear();
    future = QtConcurrent::filter(inList,filter);
    futureWatcher.setFuture(future);
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    filterValue= arg1;
}
