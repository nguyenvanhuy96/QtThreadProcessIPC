#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFuture>
#include <QDebug>
#include <QThread>
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
    static void heavyWork();
private slots:
    void on_btnStart_clicked();

    void on_btnCancel_clicked();

    void on_btnStop_clicked();

    void on_btnResume_clicked();

private:
    Ui::Widget *ui;
    QFuture<void> future;
};
#endif // WIDGET_H
