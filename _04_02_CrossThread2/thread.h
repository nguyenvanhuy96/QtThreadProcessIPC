#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "producer.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(Producer * producer,QObject *parent = nullptr);
private:
    Producer *m_producer;


    // QThread interface
protected:
    void run() override;
};

#endif // THREAD_H
