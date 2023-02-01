#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "producer.h"
#include "consumer.h"
#include <QThread>
#include <QDebug>
#include "thread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    Producer * producer;
    Consumer* consumer;
    Thread * thread;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
#endif // WIDGET_H
