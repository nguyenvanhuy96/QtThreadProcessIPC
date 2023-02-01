#include "widget.h"
#include "ui_widget.h"
#include <QCloseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "GUI:" << QThread::currentThread();

    producer = new Producer(this);
    ui->verticalLayout->addWidget(producer);
    consumer = new Consumer();

    thread = new QThread(this);


    // do queued connect
    connect(producer, &Producer::data, consumer, &Consumer::data);
    connect(thread, &QThread::started, producer, &Producer::startProduction);
    connect(thread, &QThread::finished, consumer, &QObject::deleteLater);

    consumer->moveToThread(thread);
    thread->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    thread->quit();
    event->accept(); // nếu không có khi tắt đột ngột sẽ thông báo lỗi đỏ
}

