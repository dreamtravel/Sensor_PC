/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the multimeter interface class of Sensor platform system software.
**
*****************************************************************************/

#include "multimeterwidget.h"
#include "ui_multimeterwidget.h"

MultimeterWidget::MultimeterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultimeterWidget)
{
    ui->setupUi(this);

    ui->pushButton_Close->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    ui->pushButton_A->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    ui->pushButton_P->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    ui->pushButton_T->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    type = 1;
}

MultimeterWidget::~MultimeterWidget()
{
    delete ui;
}

void MultimeterWidget::on_pushButton_Close_clicked()
{
    emit closeCurrentPage();
}

void MultimeterWidget::on_pushButton_A_clicked()
{
    type = 1;
    ui->label->setText(QObject::tr("电流"));
    ui->lcdNumber->display(temp[0]);
}

void MultimeterWidget::on_pushButton_P_clicked()
{
    type = 2;
    ui->label->setText(QObject::tr("压力"));
    ui->lcdNumber->display(temp[1]);
}

void MultimeterWidget::on_pushButton_T_clicked()
{
    type = 3;
    ui->label->setText(QObject::tr("温度"));
    ui->lcdNumber->display(temp[2]);
}

void MultimeterWidget::getData(Data *data)
{
    temp[0]=data->amp;
    temp[1]=data->inam;
    temp[2]=data->the;
    switch(type){
    case TYPE_A://电流
        ui->lcdNumber->display( temp[0]);
        break;
    case TYPE_P://压力
        ui->lcdNumber->display(temp[1]);
        break;
    case TYPE_T://温度
        ui->lcdNumber->display(temp[2]);
        break;
    default:
        break;
    }
}
