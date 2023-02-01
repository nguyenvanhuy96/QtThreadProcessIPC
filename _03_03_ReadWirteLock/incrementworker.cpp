#include "incrementworker.h"

IncrementWorker::IncrementWorker(bool *stop, PrintDevice *printDevice,QObject *parent)
    : QThread(parent), m_stop(stop), m_printDevice(printDevice)
{

}

IncrementWorker::~IncrementWorker()
{

}

void IncrementWorker::run()
{
while(!(*m_stop)){
    msleep(1500);
    m_printDevice->increment();
}
}
