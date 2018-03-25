/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the allsensor interface class of Sensor platform system software.
**
*****************************************************************************/

#include "allsensorwidget.h"
#include "ui_allsensorwidget.h"
extern Sensor_Info_All sensor_info_all;
AllSensorWidget::AllSensorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllSensorWidget)
{
    UiInitialize();
}

AllSensorWidget::~AllSensorWidget()
{
    delete ui;
}

void AllSensorWidget::UiInitialize()
{
    ui->setupUi(this);
    ui->pushButton_Close->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
}

void AllSensorWidget::on_pushButton_Close_clicked()
{
    emit closeCurrentPage();
}

void AllSensorWidget::getData(Data *data)
{
    //Int
      //干簧门磁/霍尔开关
       if(data->hall.a == 2){
           ui->label_io_1->setText(QObject::tr("正常"));
       }
       else if(data->hall.a == 3){
           ui->label_io_1->setText(QObject::tr("异常"));
       }
       if(data->hall.b == 0){
           ui->label_io_2->setText(QObject::tr("正常"));
       }
       else if(data->hall.b == 1){
           ui->label_io_2->setText(QObject::tr("异常"));
       }
       //广谱气体传感器
       if(data->gas == 0){
           ui->label_io_3->setText(QObject::tr("正常"));
       }
       else if(data->gas == 1){
           ui->label_io_3->setText(QObject::tr("异常"));
       }
       //红外对射传感器
       if(data->irds == 0){
           ui->label_io_4->setText(QObject::tr("正常"));
       }
       else if(data->irds == 1){
           ui->label_io_4->setText(QObject::tr("异常"));
       }
       //接近/红外反射传感器
       if(data->irfs.b == 0){
           ui->label_io_5->setText(QObject::tr("正常"));
       }
       else if(data->irfs.b == 1){
           ui->label_io_5->setText(QObject::tr("异常"));
       }
       if(data->irfs.a == 2){
           ui->label_io_6->setText(QObject::tr("正常"));
       }
       else if(data->irfs.a == 3){
           ui->label_io_6->setText(QObject::tr("异常"));
       }
       //热释红外传感器
       if(data->rsir == 0){
           ui->label_io_7->setText(QObject::tr("正常"));
       }
       else if(data->rsir == 1){
           ui->label_io_7->setText(QObject::tr("异常"));
       }
       //声响开关/光敏
       if(data->mcph.a == 0){
           ui->label_io_8->setText(QObject::tr("正常"));
       }
       else if(data->mcph.a == 1){
           ui->label_io_8->setText(QObject::tr("异常"));
       }
       if(data->mcph.b == 2){
           ui->label_io_9->setText(QObject::tr("正常"));
       }
       else if(data->mcph.b == 3){
           ui->label_io_9->setText(QObject::tr("异常"));
       }
       //雨雪传感器
       if(data->rnsw == 0){
           ui->label_io_10->setText(QObject::tr("正常"));
       }
       else if(data->rnsw == 1){
           ui->label_io_10->setText(QObject::tr("异常"));
       }
       //震动传感器
       if(data->shk == 0){
           ui->label_io_11->setText(QObject::tr("正常"));
       }
       else if(data->shk == 1){
           ui->label_io_11->setText(QObject::tr("异常"));
       }

    //IIC Sensor
    //三轴加速度传感器
    ui->label_i2c_1->setNum(data->trac.x);
    ui->label_i2c_2->setNum(data->trac.y);
    ui->label_i2c_3->setNum(data->trac.z);
    //磁场强度传感器
    ui->label_i2c_4->setNum(data->mfs.x);
    ui->label_i2c_5->setNum(data->mfs.y);
    ui->label_i2c_6->setNum(data->mfs.z);
    //光照强度传感器
    ui->label_i2c_7->setText(QString::number(data->ilin,'f',2));
    //气压传感器
    ui->label_i2c_8->setText(QString::number(data->aipr,'f',2));
    //温湿度传感器
    ui->label_i2c_9->setText(QString::number(data->sht.a,'f',2));
    ui->label_i2c_10->setText(QString::number(data->sht.b,'f',2));

    //ADC Sensor
    //单轴倾角传感器
    ui->label_adc_1->setText(QString::number(data->dip,'f',2));
    //电流传感器
    ui->label_adc_2->setText(QString::number(data->amp,'f',2));
    //粉尘传感器
    ui->label_adc_3->setNum(data->dust);
    //颜色传感器
    ui->label_adc_4->setNum(data->ircj.x);
    ui->label_adc_10->setNum(data->ircj.y);
    ui->label_adc_11->setNum(data->ircj.z);
    //仪表放大
    ui->label_adc_5->setText(QString::number(data->inam,'f',2));
    //紫外线传感器
    ui->label_adc_6->setNum(data->ulr);
    //热电偶传感器
    ui->label_spi_1->setText(QString::number(data->the,'f',2));
}
