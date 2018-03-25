/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the weather interface class of Sensor platform system software.
**
*****************************************************************************/

#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "serial/data.h"

namespace Ui {
class WeatherWidget;
}

class WeatherWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WeatherWidget(QWidget *parent = 0);
    ~WeatherWidget();

signals:
    void closeCurrentPage();
    
private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Query_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Return_clicked();

private slots:
    void getData(Data *data);
    void getCurTime();
    void clearText();

private:
    Ui::WeatherWidget *ui;
    QSqlTableModel *model;
};

#endif // WEATHERWIDGET_H
