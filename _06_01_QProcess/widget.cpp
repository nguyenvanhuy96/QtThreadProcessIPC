#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_process = new QProcess(this);
    connect(m_process, &QProcess::started, [](){
        qDebug() << "Started process!";
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStartProcess_clicked()
{
    QString pathExe= "C:\\Qt\\Qt5.12.5\\5.12.5\\mingw73_64\\bin\\linguist.exe";
    m_process->start(pathExe);
}

void Widget::on_btnCloseProcess_clicked()
{
    m_process->close();
}


