/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is part of the Sensor Data Analysis Thread.
**
*****************************************************************************/

#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QThread>
#include "serial/win_qextserialport.h"
#include "sys/sysinfo.h"

class DataAnalysis : public QThread
{
    Q_OBJECT

private:
    int state; // 数据解析标志位
    int len; // 长度域
    int temp_len; // 已读取字节标志
    int type; // 类型域
    uchar data[4], buffer[10];


public:
    DataAnalysis();
    ~DataAnalysis();
    int COMOpen();
    Win_QextSerialPort *myCom;
    void run();
    void stop();
    int setPort(QString port,BaudRateType baud);
protected:
    int runFlag;

private:
    void dataProcessing();

signals:
};

#endif // DATAANALYSIS_H
