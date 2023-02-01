#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QThread>
#include <QString>
#include <QMutex>
#include <QDebug>
#include <QMutexLocker>

class PrintWorker : public QThread
{
    Q_OBJECT
public:
    explicit PrintWorker(QString name, bool * stop, QMutex * mutex,QObject *parent = nullptr);
    ~PrintWorker() override;
signals:
public slots:
private:
    QString m_name;
    bool * m_stop;
    QMutex * m_mutex;
    // QThread interface
protected:
    void run() override;
};

#endif // PRINTWORKER_H
