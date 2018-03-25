#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>

class UpdateThread : public QThread
{
    Q_OBJECT
public:
    explicit UpdateThread(QObject *parent = 0);

protected:
    void run();
    
signals:
    void TimeOut();
    
};

#endif // UPDATETHREAD_H
