#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "workerthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void on_btnInfo_clicked();
private:
    Ui::Widget *ui;
    WorkerThread * thread;
};
#endif // WIDGET_H
