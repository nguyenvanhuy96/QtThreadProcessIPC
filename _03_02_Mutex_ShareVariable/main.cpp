#include <QApplication>
#include <printdevice.h>
#include <printworker.h>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool stopFlag = false;

     QMutex mutex;
     PrintDevice printDevice;
     PrintWorker black("Black", &stopFlag, &printDevice);
     PrintWorker white("White", &stopFlag, &printDevice);

     black.start();
     white.start();

     QMessageBox::information(nullptr, "QMutex", "Thread working. Close me to stop");
     stopFlag = true;

     black.wait(); // Gặp lệnh này thì thread này sẽ được joint vào thread chính, và huỷ bỏ thread này
     white.wait(); // Gặp lệnh này thì thread này sẽ được joint vào thread chính, và huỷ bỏ thread này
    return 0;
}
