/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This Class provide the sensor data calculation method.
**
*****************************************************************************/

#ifndef DATACALCULATE_H
#define DATACALCULATE_H

#include "serial/data.h"
#include "sys/sysinfo.h"

class DataCalculate
{
public:
    static double ADCGetVoltage(uchar *data);
    static ThreeInt GetMagData(uchar *data);
    static TwoDouble GetHumTempData(uchar *data);
    static ThreeInt GetReadData(uchar *data);
};

#endif // DATACALCULATE_H
