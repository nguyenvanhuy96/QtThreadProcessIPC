#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTimer>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
signals:

public slots:
    void doWork();
};

#endif // WORKER_H
