/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the navigate interface class of Sensor platform system software.
**
*****************************************************************************/

#include "navigatewidget.h"
#include "ui_navigatewidget.h"

NavigateWidget::NavigateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigateWidget)
{
    ui->setupUi(this);

    ui->pushButton_Close->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
}

NavigateWidget::~NavigateWidget()
{
    delete ui;
}

void NavigateWidget::on_pushButton_Close_clicked()
{
    emit closeCurrentPage();
}

void NavigateWidget::getData(Data *data)
{
    //磁场强度传感器
    ui->label_mx->setNum(data->mfs.x);
    ui->label_my->setNum(data->mfs.y);
    ui->label_mz->setNum(data->mfs.z);
    //三轴加速度传感器
    ui->label_tx->setNum(data->trac.x);
    ui->label_ty->setNum(data->trac.y);
    ui->label_tz->setNum(data->trac.z);
    //雨雪传感器
    if(data->rnsw == 0){
        ui->label_wea->setText(QObject::tr("晴"));
    }
    else if(data->rnsw == 1){
        ui->label_wea->setText(QObject::tr("雨"));
    }
    //温湿度传感器
    ui->label_tem->setText(QString::number(data->sht.a,'f',2));
    ui->label_hum->setText(QString::number(data->sht.b,'f',2));
    //气压传感器
    ui->label_aipr->setText(QString::number(data->aipr,'f',2));
    //单轴倾角传感器
    ui->label_dip->setText(QString::number(data->dip,'f',2));
    //震动传感器
    if(data->shk == 0){
        ui->label_shk->setText(QObject::tr("平稳"));
    }
    else if(data->shk == 1){
        ui->label_shk->setText(QObject::tr("摇晃"));
    }
    //颜色传感器
    ui->label_ircj->setNum(data->ircj.x);
    ui->label_ircj_5->setNum(data->ircj.y);
    ui->label_ircj_6->setNum(data->ircj.z);
}
