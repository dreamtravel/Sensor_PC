/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is part of the Sensor Communication Protocol Toolkit.
**
*****************************************************************************/

#ifndef SENSORPROTOCOL_H
#define SENSORPROTOCOL_H

/*
 *APPPRO:帧起始/结束域
 *APPCMD:帧命令域
 *APPTYP:传感器类型
 */
#define APPPRO_SOP_INFO             0xF5 // 协议起始位
#define APPPRO_FCS_INFO             0xFF // 协议结束位

#define APPCMD_GET_ONE_SENSORINFO   0x01 // 用于获取特定传感器的信息
#define APPCMD_GET_SENSORINFO       0x02 // 用于获取所有传感器的信息
#define APPCMD_GET_IO_INFO          0x03 // 用于获取I/O类型传感器的信息
#define APPCMD_GET_I2C_INFO         0x04 // 用于获取I2C类型传感器的信息
#define APPCMD_GET_ADC_INFO         0x05 // 用于获取ADC类型传感器的信息
#define APPCMD_GET_SPI_INFO         0x06 // 用于获取SPI类型传感器的信息

#define APPTYP_HALL_INFO            0x01 // 干簧门磁/霍尔开关
#define APPTYP_GAS_INFO             0x02 // 广谱气体传感器
#define APPTYP_IRDS_INFO            0x03 // 红外对射传感器
#define APPTYP_IRFS_INFO            0x04 // 接近/红外反射传感器
#define APPTYP_RSIR_INFO            0x05 // 热释红外传感器
#define APPTYP_MCPH_INFO            0x06 // 声响开关/光敏
#define APPTYP_RNSW_INFO            0x07 // 雨雪传感器
#define APPTYP_SHK_INFO             0x08 // 震动传感器
#define APPTYP_MFS_INFO             0x10 // 磁场强度传感器
#define APPTYP_ILIN_INFO            0x11 // 光照强度传感器
#define APPTYP_AIPR_INFO            0x12 // 气压传感器
#define APPTYP_TRAC_INFO            0x13 // 三轴加速度传感器
#define APPTYP_SHT_INFO             0x14 // 温湿度传感器
#define APPTYP_DIP_INFO             0x20 // 单轴倾角传感器
#define APPTYP_AMP_INFO             0x21 // 电流传感器
#define APPTYP_DUST_INFO            0x22 // 粉尘传感器
#define APPTYP_IRCJ_INFO            0x23 // 颜色传感器
#define APPTYP_INAM_INFO            0x24 // 仪表放大
#define APPTYP_ULR_INFO             0x25 // 紫外线传感器
#define APPTYP_THE_INFO             0x30 // 热电偶传感器

#define SOP_STATE                   0x01 // 起始位
#define LEN_STATE                   0x02 // 长度位
#define TYPE_STATE                  0x03 // 类型位
#define DATA_STATE                  0x04 // 数据位
#define FCS_STATE                   0x05 // 结束位

#define LENGTH_1BYTE                0x01 // 1个字节长度

/*
 *函数名:allSensorInfoCMD
 *函数功能描述:获取所有传感器信息指令
 *函数参数:data-指令存储数组  cmd-帧命令域
 *函数返回值:无
 */
inline void allSensorInfoCMD(unsigned char* data)
{
    data[0] = APPPRO_SOP_INFO;
    data[1] = LENGTH_1BYTE;
    data[2] = APPCMD_GET_SENSORINFO;
    data[3] = APPPRO_FCS_INFO;
}

#endif // SENSORPROTOCOL_H
