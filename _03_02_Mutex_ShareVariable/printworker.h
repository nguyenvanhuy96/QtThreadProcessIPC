#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QThread>
#include <QString>
#include <QMutex>
#include <QString>
#include "printdevice.h"

class PrintWorker : public QThread
{
    Q_OBJECT
public:
    explicit PrintWorker(QString name, bool * stop, PrintDevice * printDevice,QObject *parent = nullptr);
    ~PrintWorker() override;
signals:

public slots:
private :
    QString m_name;
    bool * m_stop;
    PrintDevice * m_printDevice;

    // QThread interface
protected:
    void run() override;
};

#endif // PRINTWORKER_H
