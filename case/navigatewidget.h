/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the navigate interface class of Sensor platform system software.
**
*****************************************************************************/

#ifndef NAVIGATEWIDGET_H
#define NAVIGATEWIDGET_H

#include <QWidget>
#include "serial/data.h"

namespace Ui {
class NavigateWidget;
}

class NavigateWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit NavigateWidget(QWidget *parent = 0);
    ~NavigateWidget();

signals:
    void closeCurrentPage();
    
private slots:
    void on_pushButton_Close_clicked();

private slots:
    void getData(Data *data);

private:
    Ui::NavigateWidget *ui;
};

#endif // NAVIGATEWIDGET_H
