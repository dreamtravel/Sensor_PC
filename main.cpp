/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**Sensor Platform System Software
**
**Author: anld
**QQ:550962772
**
*****************************************************************************/

#include <QApplication>
#include <QMessageBox>
#include "mainwidget.h"
#include "sys/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString sqlpath=a.applicationDirPath();
    sqlpath +=QString("/plugins");
    a.addLibraryPath(sqlpath);
    MainWidget w;
    w.setFixedSize(800,480);
    if(!initDatabase())
        QMessageBox::warning(&w,"Warning","Failed to initialize database!");

    w.show();

    return a.exec();
}
