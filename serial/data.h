#ifndef DATA_H
#define DATA_H

#include "dataanalysis.h"
#include "sys/sysinfo.h"
#include <QObject>
#include <QTimer>

typedef struct TwoInt //双Int数据型传感器
{
    int a;
    int b;
}TwoInt;

typedef struct TwoDouble //双Double数据型传感器
{
    double a;
    double b;
}TwoDouble;

typedef struct Sensor_Info_All //所有传感器数据信息
{
    unsigned char HALL_Info[2];
    unsigned char GAS_Info;
    unsigned char IRDS_Info;
    unsigned char IRFS_Info[2];
    unsigned char RSIR_Info;
    unsigned char MCPH_Info[2];
    unsigned char RNSW_Info;
    unsigned char SHK_Info;

    unsigned char MFS_Info[6];
    unsigned char BH1750_Info[2];
    unsigned char AIPR_Info[2];
    unsigned char TRAC_Info[6];
    unsigned char SHT_Info[4];

    unsigned char DIP_Info[2];
    unsigned char AMP_Info[2];
    unsigned char DUST_Info[2];
    unsigned char IRCJ_Info[3];
    unsigned char INAM_Info[2];
    unsigned char ULR_Info[2];
    unsigned char THE_Info[2];
}Sensor_Info_All;

typedef struct ThreeInt //三Int数据型传感器
{
    int x;
    int y;
    int z;
}ThreeInt;

/*****************************************************************************************************
 * 传感器变量定义表
 *****************************************************************************************************
 *    干簧门磁/霍尔开关：hall      广谱气体传感器：gas      红外对射传感器：irds    接近/红外反射传感器：irfs
 *    热释红外传感器：rsir         声响开关/光敏：mcph      雨雪传感器：rnsw       震动传感器：shk
 *    磁场强度传感器：mfs          光照强度传感器：ilin     气压传感器：aipr       三轴加速度传感器：trac
 *    温湿度传感器：sht           单轴倾角传感器：dip       电流传感器：amp        粉尘传感器：dust
 *    红外测距传感器：ircj         压力传感器：inam         紫外线传感器：ulr      热电偶传感器：the
 *
 *****************************************************************************************************/
class Data : public QObject
{
    Q_OBJECT
public:
    Data();
    TwoInt hall, irfs, mcph;
    ThreeInt mfs,ircj, trac;
    TwoDouble sht;
    uchar gas, irds, rsir, rnsw, shk;
    double ilin, dip;
    float aipr, amp, dust,inam, ulr, the;

private:
private slots:
    void dataReceive(); // 数据接收槽函数
};

#endif // DATA_H
