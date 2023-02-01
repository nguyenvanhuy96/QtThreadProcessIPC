#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QThread>

class Worker : public QRunnable
{
public:
    explicit Worker();
   ~Worker() override;
public:
    void run() override;
};

#endif // WORKER_H
