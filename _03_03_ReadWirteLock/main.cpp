#include <QApplication>
#include "printdevice.h"
#include "printworker.h"
#include "incrementworker.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool stopFlag = false;
    PrintDevice printDevice;
    PrintWorker white("white", &stopFlag, &printDevice);
    PrintWorker black("black", &stopFlag, &printDevice);
    IncrementWorker incrementWorker(&stopFlag, &printDevice);

    white.start();
    black.start();
    incrementWorker.start();

    QMessageBox::information(nullptr, "QMutex", "Thread working, close me to stop!");
    stopFlag= true   ;

    white .wait();
    black.wait();
    incrementWorker.wait();

    return 0;
}
