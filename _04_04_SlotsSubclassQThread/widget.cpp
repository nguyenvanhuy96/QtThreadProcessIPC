#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "GUI Thread: " << QThread::currentThread();

    thread = new Thread(this);
    thread->start();
}

Widget::~Widget()
{
    delete ui;

}

