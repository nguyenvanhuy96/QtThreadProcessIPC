#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
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

private slots:
    void on_btnStartProcess_clicked();
    void on_btnCloseProcess_clicked();
private:
    Ui::Widget *ui;
    QProcess * m_process;
};
#endif // WIDGET_H
