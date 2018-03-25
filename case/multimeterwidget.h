/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the multimeter interface class of Sensor platform system software.
**
*****************************************************************************/

#ifndef MULTIMETERWIDGET_H
#define MULTIMETERWIDGET_H

#include <QWidget>
#include "serial/data.h"

#define TYPE_A      1 //电流
#define TYPE_P      2 //压力
#define TYPE_T      3 //温度

namespace Ui {
class MultimeterWidget;
}

class MultimeterWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MultimeterWidget(QWidget *parent = 0);
    ~MultimeterWidget();

signals:
    void closeCurrentPage();
    
private slots:
    void on_pushButton_Close_clicked();

    void on_pushButton_A_clicked();

    void on_pushButton_P_clicked();

    void on_pushButton_T_clicked();

private slots:
    void getData(Data *data);

private:
    Ui::MultimeterWidget *ui;
    int type;//指示当前测量类型
    float temp[3];
};

#endif // MULTIMETERWIDGET_H
