#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "worker.h"
#include <QThreadPool>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;
private slots:
    void on_btnStart_clicked();
public slots:
    void gotUpdate(int value);
};
#endif // WIDGET_H
