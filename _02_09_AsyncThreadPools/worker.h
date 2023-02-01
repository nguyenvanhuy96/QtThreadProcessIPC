#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QThread>
#include <QTimer>

class Worker : public QRunnable
{
public:
    explicit Worker(QObject *receiver);
   ~Worker() override;
public:
    void run() override;
private:
   QObject *m_receiver;
};

#endif // WORKER_H
