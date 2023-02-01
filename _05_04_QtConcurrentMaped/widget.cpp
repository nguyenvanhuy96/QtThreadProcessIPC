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
        qDebug() << "Result count: " << future.resultCount();
        qDebug() << "Result count: " << future.results();
    });
    connect(&futureWatcher, &QFutureWatcher<void>::progressValueChanged,[=](int value){
        qDebug() << "Progress changed to value:" << value;
    });
}

Widget::~Widget()
{
    delete ui;
}

int Widget::modify(const int &value)
{
    qDebug() << "Modifying " <<value   << " result: " << value*10 << " Thread: " << QThread::currentThread();
    return value*10;
}


void Widget::on_btnModify_clicked()
{
    /* Cách viết này nó sẽ bị overload
    auto modify= [=](const int & value){
        qDebug() << "Modifying " <<value   << " result: " << value*10 << " Thread: " << QThread::currentThread();
        return value*10;
    };
    */
std::function<int(const int &)> modify = [](const int & value){
    qDebug() << "Modifying " <<value   << " result: " << value*10 << " Thread: " << QThread::currentThread();
    return value*10;
};

future = QtConcurrent::mapped(list,modify);
    futureWatcher.setFuture(future);
}

void Widget::on_btnViewResult_clicked()
{
   qDebug() << "Modified value: " <<list.last();
}
