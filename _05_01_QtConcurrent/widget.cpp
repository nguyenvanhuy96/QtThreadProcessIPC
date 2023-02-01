#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "GUI thread: " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::heavyWork()
{
    qDebug() << "Heavy work running in thread: " << QThread::currentThread();

    for (int i{0}; i <1000000000; i++) {
        if((i% 100000) ==0){
            double percentage = (i/1000000000.0)*100;
            qDebug() << "Percentage: " << QVariant::fromValue(percentage).toInt() <<
                        " Thread: " << QThread::currentThread();
        }
    }
}


void Widget::on_btnStart_clicked()
{
    future  = QtConcurrent::run(heavyWork);
    // waitForFinished: chờ đến đoạn code này nó mới chạy tiếp,
    // lúc chờ thì công việc đang chạy ở 1 thread khác => block ui lại, coi như nó chạy ở luồng hiện tại luôn
    //    future.waitForFinished();
    //    qDebug() << "Computation done";
}

void Widget::on_btnCancel_clicked()
{
    future.cancel(); // không làm việc
}

void Widget::on_btnStop_clicked()
{
    future.pause(); // không làm việc
}

void Widget::on_btnResume_clicked()
{
    future.resume(); // không làm việc
}
