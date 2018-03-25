#ifndef MYDELAY_H
#define MYDELAY_H

#include "updatethread.h"

class MyDelay : public UpdateThread
{
public:
    MyDelay(int sec);

private:
    int sec;

protected:
    void run();
};

#endif // MYDELAY_H
