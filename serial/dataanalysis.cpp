/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is part of the Sensor Data Analysis Thread.
**
*****************************************************************************/

#include "dataanalysis.h"
#include "cmd/sensorprotocol.h"
#include "serial/data.h"
#include <stddef.h>
#include <QMessageBox>

DataAnalysis::DataAnalysis()
{
    runFlag=1;
    state = SOP_STATE;
    allSensorInfoCMD(data);
    myCom = new Win_QextSerialPort("COM1", QextSerialBase::Polling);
}

DataAnalysis::~DataAnalysis()
{
    myCom->close();
}

int DataAnalysis::COMOpen()
{
    if(myCom->open(QIODevice::ReadWrite))
    {
        myCom->setBaudRate(BAUD115200);
        myCom->setFlowControl(FLOW_OFF);
        myCom->setTimeout(10);
        myCom->setDataBits(DATA_8);
        myCom->setStopBits(STOP_1);
        myCom->setParity(PAR_NONE);
        return 1;
    }
    else
    {
        QMessageBox::information(NULL,tr("提示："),tr("串口被占用"));
        return 0;
    }
}
void DataAnalysis::run()
{
    while(runFlag){
        myCom->write((const char*)data, 4);
        dataProcessing();
        sleep(2);
    }
}
void DataAnalysis::stop()
{
    runFlag=0;
    myCom->close();
    delete myCom;
}
int DataAnalysis::setPort(QString port,BaudRateType baud)
{
    myCom = new Win_QextSerialPort(port, QextSerialBase::Polling);
    myCom->flush();
    if(myCom->open(QIODevice::ReadWrite))
    {
        myCom->setBaudRate(baud);
        myCom->setFlowControl(FLOW_OFF);
        myCom->setTimeout(10);
        myCom->setDataBits(DATA_8);
        myCom->setStopBits(STOP_1);
        myCom->setParity(PAR_NONE);
        runFlag=1;
        this->start();
        return 1;
    }
    else
    {
        QMessageBox::information(NULL,tr("提示："),tr("打开失败"));
        runFlag=0;
        return 0;
    }
}
/*
 *函数名:dataProcessing
 *函数功能描述:按照通信协议对串口数据进行解析并发送
 *函数参数:无
 *函数返回值:无
 */
void DataAnalysis::dataProcessing()
{
    uchar ch;
    int available;
    extern Sensor_Info_All sensor_info_all;
    while(myCom->bytesAvailable() > 0){ // 判断串口是否有可度数据
        myCom->read((char*)&ch, 1);
        switch(state){
        /*读取帧起始域*/
        case SOP_STATE:
            if(ch == APPPRO_SOP_INFO)
                state = LEN_STATE;
            break;

        /*读取帧长度域，帧长度域为 TYPE+DATA */
        case LEN_STATE:
            len = ch - 1; // 去除1字节的TYPE位
            temp_len = 0; // 初始化已读取字节标志

            state = TYPE_STATE;
            break;

        /*读取传感器类型*/
        case TYPE_STATE:
            type = ch;
            if(len > 0)
                state = DATA_STATE;
            else
                state = FCS_STATE;
            break;

        /*读取帧数据域*/
        case DATA_STATE:
            buffer[temp_len++] = ch;
            available = myCom->bytesAvailable();
            /*缓存数据不足，将缓存数据全部读取*/
            if(available <= len - temp_len){
                myCom->read((char*)&buffer[temp_len], available);
                temp_len += available;
            }
            /*缓存数据充足，仅读取数据域剩余部分*/
            else{
                myCom->read((char*)&buffer[temp_len], len-temp_len);
                temp_len += (len - temp_len);
            }

            if(temp_len == len)
                state = FCS_STATE;
            break;

        /*读取帧结束域*/
        case FCS_STATE:
            if(ch == APPPRO_FCS_INFO){
                //switch 语句的嵌套使用
                switch(type){
                case APPTYP_HALL_INFO: //干簧门磁/霍尔开关
                    sensor_info_all.HALL_Info[0]=buffer[0];
                    sensor_info_all.HALL_Info[1]=buffer[1];
                    break;
                case APPTYP_GAS_INFO: //广谱气体传感器
                   sensor_info_all.GAS_Info=buffer[0];
                    break;
                case APPTYP_IRDS_INFO: //红外对射传感器
                    sensor_info_all.IRDS_Info=buffer[0];
                    break;
                case APPTYP_IRFS_INFO: //接近/红外反射传感器
                    sensor_info_all.IRFS_Info[0]=buffer[0];
                    sensor_info_all.IRFS_Info[1]=buffer[1];
                    break;
                case APPTYP_RSIR_INFO: //热释红外传感器
                    sensor_info_all.RSIR_Info=buffer[0];
                    break;
                case APPTYP_MCPH_INFO: //声响开关/光敏
                    sensor_info_all.MCPH_Info[0]=buffer[0];
                    sensor_info_all.MCPH_Info[1]=buffer[1];
                    break;
                case APPTYP_RNSW_INFO: //雨雪传感器
                   sensor_info_all.RNSW_Info=buffer[0];
                    break;
                case APPTYP_SHK_INFO: //震动传感器
                    sensor_info_all.SHK_Info=buffer[0];
                    break;

                case APPTYP_MFS_INFO: //磁场强度传感器
                    for(int i=0;i<6;i++)
                        sensor_info_all.MFS_Info[i]=buffer[i];
                    break;
                case APPTYP_ILIN_INFO: //光照强度传感器
                    sensor_info_all.BH1750_Info[0]=buffer[0];
                    sensor_info_all.BH1750_Info[1]=buffer[1];
                    break;
                case APPTYP_AIPR_INFO: //气压传感器
                    sensor_info_all.AIPR_Info[0]=buffer[0];
                    sensor_info_all.AIPR_Info[1]=buffer[1];
                    break;
                case APPTYP_TRAC_INFO: //三轴加速度传感器
                    for(int i=0;i<6;i++)
                        sensor_info_all.TRAC_Info[i]=buffer[i];
                    break;
                case APPTYP_SHT_INFO: //温湿度传感器
                    for(int i=0;i<4;i++)
                        sensor_info_all.SHT_Info[i]=buffer[i];
                    break;
                case APPTYP_DIP_INFO: //单轴倾角传感器
                    sensor_info_all.DIP_Info[0]=buffer[0];
                    sensor_info_all.DIP_Info[1]=buffer[1];
                    break;
                case APPTYP_AMP_INFO: //电流传感器
                    sensor_info_all.AMP_Info[0]=buffer[0];
                    sensor_info_all.AMP_Info[1]=buffer[1];
                    break;
                case APPTYP_DUST_INFO: //粉尘传感器
                    sensor_info_all.DUST_Info[0]=buffer[0];
                    sensor_info_all.DUST_Info[1]=buffer[1];
                    break;
                case APPTYP_IRCJ_INFO: //颜色传感器
                    sensor_info_all.IRCJ_Info[0]=buffer[0];
                    sensor_info_all.IRCJ_Info[1]=buffer[1];
                    sensor_info_all.IRCJ_Info[2]=buffer[2];
                    break;
                case APPTYP_INAM_INFO: //仪表放大
                    sensor_info_all.INAM_Info[0]=buffer[0];
                    sensor_info_all.INAM_Info[1]=buffer[1];
                    break;
                case APPTYP_ULR_INFO: //紫外线传感器
                    sensor_info_all.ULR_Info[0]=buffer[0];
                    sensor_info_all.ULR_Info[1]=buffer[1];
                    break;
                case APPTYP_THE_INFO: //热电偶传感器
                    sensor_info_all.THE_Info[0]=buffer[0];
                    sensor_info_all.THE_Info[1]=buffer[1];
                    break;
                default:
                    break;
                }
               // emit dataSend();
            }

            state = SOP_STATE;
            break;

        default:
            break;
        }
    }
}
