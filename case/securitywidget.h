/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the security interface class of Sensor platform system software.
**
*****************************************************************************/

#ifndef SECRUITYWIDGET_H
#define SECRUITYWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "serial/data.h"

namespace Ui {
class SecurityWidget;
}

class SecurityWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SecurityWidget(QWidget *parent = 0);
    ~SecurityWidget();

signals:
    void closeCurrentPage();
    
private slots:
    void on_pushButton_Sensor1_clicked();

    void on_pushButton_Sensor2_clicked();

    void on_pushButton_Sensor3_clicked();

    void on_pushButton_Sensor4_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Return_clicked();

private slots:
    void getData(Data *data);

    void on_pushButton_Query_clicked();

private:
    Ui::SecurityWidget *ui;
    QSqlTableModel *model;
};

#endif // SECRUITYWIDGET_H
