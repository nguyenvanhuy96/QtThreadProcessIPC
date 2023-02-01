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

}

Widget::~Widget()
{
    delete ui;
}

void Widget::reduce(int &sum, int value)
{
  sum += value;
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
    future = QtConcurrent::filtered(inList,filter);
    future.waitForFinished();

    // Sync code
    qDebug() << "Synchronous: Work finished.";
    ui->lstwDes->clear();
    QList<int> newList = future.results();
    qDebug() << "Modified list " <<newList;
    foreach(int number, newList){
        ui->lstwDes->addItem(QString::number(number));
    }

    // using filteredReduce
    auto future2 = QtConcurrent::filteredReduced(inList,filter, reduce);
    future2.waitForFinished();
    int total = future2.result();
    qDebug() << "Total: " << QString::number(total);
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    filterValue= arg1;
}
