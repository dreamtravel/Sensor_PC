/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the security interface class of Sensor platform system software.
**
*****************************************************************************/

#include "securitywidget.h"
#include "ui_securitywidget.h"
#include <QDateTime>
#include <QString>
#include <QSqlQuery>

SecurityWidget::SecurityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecurityWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_Sensor1->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/security-sensor/sensor1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/security-sensor/sensor1-hover.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/security-sensor/sensor1-pressed.png);}");
    ui->pushButton_Sensor2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/security-sensor/sensor2.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/security-sensor/sensor2-hover.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/security-sensor/sensor2-pressed.png);}");
    ui->pushButton_Sensor3->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/security-sensor/sensor3.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/security-sensor/sensor3-hover.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/security-sensor/sensor3-pressed.png);}");
    ui->pushButton_Sensor4->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/security-sensor/sensor4.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/security-sensor/sensor4-hover.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/security-sensor/sensor4-pressed.png);}");

    ui->pushButton_Close->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    ui->pushButton_Return->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    ui->pushButton_Query->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
}

SecurityWidget::~SecurityWidget()
{
    delete ui;
}

void SecurityWidget::on_pushButton_Sensor1_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("kitchen");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->stackedWidget->setCurrentIndex(1);
}

void SecurityWidget::on_pushButton_Sensor2_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("door");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->stackedWidget->setCurrentIndex(1);
}

void SecurityWidget::on_pushButton_Sensor3_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("carport");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->stackedWidget->setCurrentIndex(1);
}

void SecurityWidget::on_pushButton_Sensor4_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("window");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->stackedWidget->setCurrentIndex(1);
}

void SecurityWidget::on_pushButton_Close_clicked()
{
    emit closeCurrentPage();
}

void SecurityWidget::on_pushButton_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void SecurityWidget::getData(Data *data)
{
    //干簧门磁
    if(data->hall.a == 0){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Door->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/normal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into door (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("门"));
        query.addBindValue(QObject::tr("正常"));
        query.exec();
    }
    else if(data->hall.a == 1){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Door->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/abnormal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into door (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("门"));
        query.addBindValue(QObject::tr("异常"));
        query.exec();
    }
    //红外对射传感器
    if(data->irds == 0){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Window->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/normal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into window (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("窗"));
        query.addBindValue(QObject::tr("正常"));
        query.exec();
    }
    else if(data->irds == 1){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Window->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/abnormal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into window (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("窗"));
        query.addBindValue(QObject::tr("异常"));
        query.exec();
    }
    //广谱气体传感器
    if(data->gas == 0){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Kitchen->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/normal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into kitchen (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("厨房"));
        query.addBindValue(QObject::tr("正常"));
        query.exec();
    }
    else if(data->gas == 1){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Kitchen->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/abnormal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into kitchen (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("厨房"));
        query.addBindValue(QObject::tr("异常"));
        query.exec();
    }
    //热释红外传感器
    if(data->rsir == 0){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Carport->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/normal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into carport (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("车库"));
        query.addBindValue(QObject::tr("正常"));
        query.exec();
    }
    else if(data->rsir == 1){
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString(QObject::tr("yyyy.MM.dd hh:mm:ss"));
        ui->label_Carport->setStyleSheet("border-image: url(:/new/prefix1/res/security-sensor/abnormal.png);");

        QSqlQuery query;
        query.exec(QObject::tr("insert into carport (时间, 类型, 状态) "
                               "values(?, ?, ?)"));
        query.addBindValue(str);
        query.addBindValue(QObject::tr("车库"));
        query.addBindValue(QObject::tr("异常"));
        query.exec();
    }
}

void SecurityWidget::on_pushButton_Query_clicked()
{
    QString str = ui->comboBox->currentText();
    model->setFilter(QObject::tr("状态 = '%1'").arg(str));
    model->select();
}
