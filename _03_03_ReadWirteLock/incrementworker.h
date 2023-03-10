#ifndef INCREMENTWORKER_H
#define INCREMENTWORKER_H

#include <QThread>
#include "printdevice.h"

class IncrementWorker : public QThread
{
    Q_OBJECT
public:
    explicit IncrementWorker(bool *stop, PrintDevice *printDevice,QObject *parent = nullptr);
    ~IncrementWorker() override;
signals:

public slots:
private:
    PrintDevice * m_printDevice;
    bool * m_stop;


    // QThread interface
protected:
    void run() override;
};

#endif // INCREMENTWORKER_H
