#include "printworker.h"

PrintWorker::PrintWorker(const QString &name , bool *stop, PrintDevice * printDevice,QObject *parent)
    : QThread(parent), m_name (name), m_stop(stop), m_printDevice(printDevice)
{

}

PrintWorker::~PrintWorker()
{

}
void PrintWorker::run() {
    while(!(*m_stop)){
        m_printDevice->print(m_name );
        sleep(1);
    }
}
