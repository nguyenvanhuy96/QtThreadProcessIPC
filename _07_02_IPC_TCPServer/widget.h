#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
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
protected slots:
    void gotConnection();
    void readData();

private:
    Ui::Widget *ui;
    QTcpServer m_server;
    QTcpSocket *m_socket;
};
#endif // WIDGET_H
