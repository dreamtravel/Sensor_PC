/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the allsensor interface class of Sensor platform system software.
**
*****************************************************************************/

#ifndef ALLSENSORWIDGET_H
#define ALLSENSORWIDGET_H

#include <QWidget>
#include "serial/data.h"

namespace Ui {
class AllSensorWidget;
}

class AllSensorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit AllSensorWidget(QWidget *parent = 0);
    ~AllSensorWidget();

private:
    void UiInitialize();
    
signals:
    void closeCurrentPage();

private slots:
    void on_pushButton_Close_clicked();

private slots:
    void getData(Data *data);

private:
    Ui::AllSensorWidget *ui;
};

#endif // ALLSENSORWIDGET_H
