#include "updatethread.h"

UpdateThread::UpdateThread(QObject *parent) :
    QThread(parent)
{
}

void UpdateThread::run()
{
    while(1){
        emit TimeOut();
        sleep(2);
    }
}
