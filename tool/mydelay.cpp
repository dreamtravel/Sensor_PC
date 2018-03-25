#include "mydelay.h"

MyDelay::MyDelay(int sec)
{
    this->sec = sec;
}

void MyDelay::run()
{
    sleep(sec);
    emit TimeOut();
}
