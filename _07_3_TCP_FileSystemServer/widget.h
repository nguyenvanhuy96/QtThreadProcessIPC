#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFile>
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
    void reloadFile();

private:
    Ui::Widget *ui;
    QFileSystemWatcher *m_watcher;
    void createFileIfNotExist();
};
#endif // WIDGET_H
