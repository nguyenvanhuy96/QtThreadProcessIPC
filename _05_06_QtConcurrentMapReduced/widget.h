#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtConcurrent>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFuture>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    // utility function that recursivily searches for files
    QStringList findFiles(const QString& startDir, const QStringList& filters);
    // single threaded
    QMap<QString,int> singleThreadedWordCount(const QStringList & files);
    // countWords counts the words in a single file. this function is
    // called in parallel by several threads and must be thread
    // safe. This is the map function
   static QMap<QString,int> countWords(const QString &file);
   // reduce adds the results from map to the final
   // result. This functor will only be called by one thread
   // at a time
   static void reduce(QMap<QString,int> &result , const QMap<QString,int> &w);

private slots:
    void on_btnChooseDir_clicked();
    void on_btnFindFiles_clicked();
    void on_btnSingleThread_clicked();
    void on_btnMapReduced_clicked();
private:
    Ui::Widget *ui;
    QString chooseDir;
    QStringList files;
    QFuture<QMap<QString,int>> future;

};
#endif // WIDGET_H
