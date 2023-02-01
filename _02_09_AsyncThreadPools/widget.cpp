#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug() << "GUI thread: " << thread();
    qDebug() << "Thread(Widget): " << QThread::currentThread();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
    Worker *worker = new Worker(this);
    worker->setAutoDelete(false);
    QThreadPool::globalInstance()->start(worker);
}
