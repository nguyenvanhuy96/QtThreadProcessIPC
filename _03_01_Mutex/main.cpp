#include <QApplication>
#include "printworker.h"
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool stopFlag = false;

     QMutex mutex;
     PrintWorker black("Black", &stopFlag, &mutex);
     PrintWorker white("White", &stopFlag, &mutex);

     black.start();
     white.start();

     QMessageBox::information(nullptr, "QMutex", "Thread working. Close me to stop");
     stopFlag = true;

     black.wait(); // Gặp lệnh này thì thread này sẽ được joint vào thread chính, và huỷ bỏ thread này
     white.wait(); // Gặp lệnh này thì thread này sẽ được joint vào thread chính, và huỷ bỏ thread này
    return 0;
}
