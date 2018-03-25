/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the main interface class of Sensor platform system software.
**
*****************************************************************************/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTextCodec>
#include "case/securitywidget.h"
#include "case/weatherwidget.h"
#include "case/multimeterwidget.h"
#include "case/navigatewidget.h"
#include "case/allsensorwidget.h"
#include "serial/data.h"
#include "serial/dataanalysis.h"
#include "tool/updatethread.h"
#include <stddef.h>
#include <QDateTime>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    
private slots:
    void on_pushButton_AllSensor_clicked();

    void on_pushButton_Security_clicked();

    void on_pushButton_Weather_clicked();

    void on_pushButton_Navigate_clicked();

    void on_pushButton_Multimeter_clicked();

private slots:
    void changeToMainPage();
    void sendData();
    void on_setBtn_clicked();

private:
    Ui::MainWidget *ui;
    SecurityWidget *securityWidget;
    WeatherWidget *weatherWidget;
    MultimeterWidget *multimeterWidget;
    NavigateWidget *navigateWidget;
    AllSensorWidget *allSensorWidget;
    Data *data;
    DataAnalysis *dataAnalysis;
    UpdateThread *updateThread;

signals:
    void allSensorInfo(Data*);


private:
    void stackedWidgetInit();
};

#endif // MAINWIDGET_H
