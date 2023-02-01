#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtConcurrent>
#include <QFuture>
#include <QDebug>
#include <QFutureWatcher>
#include <QRandomGenerator>
#include <QThread>;
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
    void on_btnFilter_clicked();
    void on_spinBox_valueChanged(int arg1);
private:
    Ui::Widget *ui;
    int filterValue;
    QList<int> inList;
    QFuture<int> future;
    QFutureWatcher<int> futureWatcher;
};
#endif // WIDGET_H
