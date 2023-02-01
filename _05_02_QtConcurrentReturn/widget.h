#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    static QFuture<QVector<int>> heavyWorkWithReturn();
private slots:
    void on_btnStart_clicked();

    void on_btnCancel_clicked();

    void on_btnPause_clicked();

    void on_btnResume_clicked();

private:
    Ui::Widget *ui;
    QFuture<QVector<int>> future;
    QFutureWatcher<QVector<int>> watcher;
};
#endif // WIDGET_H
