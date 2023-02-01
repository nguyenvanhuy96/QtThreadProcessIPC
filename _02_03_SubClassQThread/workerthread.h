#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);
   ~WorkerThread() override;
signals:
   void currentCount(int value);
   void countDone();
public slots:
    // QThread interface
protected:
    void run() override; // Khi gọi sự kiện Started thì nó sẽ tự động chạy vào đây
};

#endif // WORKERTHREAD_H
