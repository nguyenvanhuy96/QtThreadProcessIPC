#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "GUI thread: " << QThread::currentThread();
    qDebug() << "Number core: " << QThread::idealThreadCount();
    // populate list
    for (int i{0};i<10; i++) {
        list<<i;
    }


    qDebug() << "Original value: "<< list.last();

    connect(&futureWatcher, &QFutureWatcher<void>::started,[=](){
        qDebug() << "Async: work stared!";
    });
    connect(&futureWatcher, &QFutureWatcher<void>::finished,[=](){
        qDebug() << "Async: work finished!";
    });
    connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,[=](int value){
        qDebug() << "Progress changed to value:" << value;
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::modify(int &value)
{
    qDebug() << "Modifying " <<value   << " result: " << value*10 << " Thread: " << QThread::currentThread();
    value = value*10;
}


void Widget::on_btnModify_clicked()
{
    // vì mỗi item trong list là kiểu int nên đâù vào sẽ là kiểu int
//    auto modify = [](int &value){
//        qDebug() << "Modifying " <<value   << " result: " << value*10 << " Thread: " << QThread::currentThread();
//        value = value*10;
//    };
    future = QtConcurrent::map(list,modify);
    futureWatcher.setFuture(future);
}

void Widget::on_btnViewResult_clicked()
{
   qDebug() << "Modified value: " <<list.last();

}
