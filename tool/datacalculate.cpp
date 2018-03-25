/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This Class provide the sensor data calculation method.
**
*****************************************************************************/

#include "datacalculate.h"
#include <math.h>

/*
 *函数名:ADCGetVoltage
 *函数功能描述:ADC类型传感器电压值计算
 *函数参数:寄存器值
 *函数返回值:实际输出电压
 */
double DataCalculate::ADCGetVoltage(uchar *data)
{
    double voltage;
    int x;
    x = data[0]*256 + data[1];
    voltage = x *3.3 / (pow(2, 12) - 1);

    return voltage;
}

/*
 *函数名:GetMagData
 *函数功能描述:磁场强度传感器数据计算
 *函数参数:寄存器值
 *函数返回值:磁场强度传感器数据
 */
ThreeInt DataCalculate::GetMagData(uchar *data)
{
    ThreeInt magData;
    magData.x = data[0]*256 + data[1];
    magData.y = data[2]*256 + data[3];
    magData.z = data[4]*256 + data[5];

    return magData;
}

/*
 *函数名:GetReadData
 *函数功能描述:获取串口数据存储到结构体中
 *函数参数:寄存器值
 *函数返回值:颜色传感器数据
 */
ThreeInt DataCalculate::GetReadData(uchar *data)
{
    ThreeInt temp;
    temp.x=data[0];
    temp.y=data[1];
    temp.z=data[2];
    return temp;
}
/*
 *函数名:GetHumTempData
 *函数功能描述:温湿度传感器数据计算
 *函数参数:寄存器值
 *函数返回值:温湿度传感器数据
 */
TwoDouble DataCalculate::GetHumTempData(uchar *data)
{
    TwoDouble sht;
     const float C1=-4.0; // for 12 Bit
     const float C2= 0.0405; // for 12 Bit
     const float C3=-0.0000028; // for 12 Bit
     const float T1=0.01; // for 14 Bit @ 5V
     const float T2=0.00008; // for 14 Bit @ 5V

     int rh= data[0]*256 + data[1]; // rh: Humidity [Ticks] 12 Bit
     int t=data[2]*256 + data[3];// t: Temperature [Ticks] 14 Bit
     float rh_lin; // rh_lin: Humidity linear
     float rh_true; // rh_true: Temperature compensated humidity
     float t_C; // t_C : Temperature [C]
     t_C=t*0.01 - 42; //calc. Temperature from ticks to [C]
     rh_lin=C3*rh*rh + C2*rh + C1; //calc. Humidity from ticks to [%RH]
     rh_true=(t_C-25)*(T1+T2*rh)+rh_lin; //calc. Temperature compensated humidity [%RH]
     if(rh_true>100)rh_true=100; //cut if the value is outside of
     if(rh_true<0.1)rh_true=0.1; //the physical possible range
     sht.a=t_C; //return temperature [C]
     sht.b=rh_true; //return humidity[%RH]
    return sht;
}
