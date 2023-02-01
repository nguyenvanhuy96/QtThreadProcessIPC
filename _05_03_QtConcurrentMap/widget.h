#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFuture>
#include <QFutureWatcher>
#include <QDebug>
#include <QtConcurrent>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
  static void modify(int &value);
private slots:
    void on_btnModify_clicked();

    void on_btnViewResult_clicked();

private:
    Ui::Widget *ui;
    QList<int> list;
    QFuture<void> future;
    QFutureWatcher<void> futureWatcher;
};
#endif // WIDGET_H
