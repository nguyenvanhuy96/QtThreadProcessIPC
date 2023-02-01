#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "UI running in thread: " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
  Worker * worker= new Worker();
  worker->setAutoDelete(false); // Sau khi chạy xong có hủy luôn thread đó không
  QThreadPool::globalInstance()->start(worker);
}

void Widget::on_btnInfo_clicked()
{

}
