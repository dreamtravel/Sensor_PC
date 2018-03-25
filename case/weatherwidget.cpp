/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the weather interface class of Sensor platform system software.
**
*****************************************************************************/

#include "weatherwidget.h"
#include "ui_weatherwidget.h"
#include "tool/mydelay.h"
#include <QDateTime>
#include <QString>
#include <QSqlQuery>
#include <QTimer>
#include<QTextCodec>

WeatherWidget::WeatherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString(QObject::tr("yyyy.MM.dd dddd (hh:mmAP)实况"));
    ui->label_time->setText(str);
    //QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getCurTime()));
    timer->start(1000);

    ui->pushButton_Save->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/weather-sensor/save1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/weather-sensor/save1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/weather-sensor/save2.png);}");
    ui->pushButton_Query->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/weather-sensor/query1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/weather-sensor/query1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/weather-sensor/query2.png);}");
    ui->pushButton_Close->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");
    ui->pushButton_Return->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/button1.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/button2.png);}");

    ui->label_notice->setWordWrap(true);
    ui->label_notice->setAlignment(Qt::AlignTop);
    ui->label_notice->setText(QObject::tr("应该避免外出，敏感的人应该呆在室内，关闭门窗。"));
}

WeatherWidget::~WeatherWidget()
{
    delete ui;
}

void WeatherWidget::on_pushButton_Save_clicked()
{
    QSqlQuery query;
    query.exec(QObject::tr("insert into weather (时间, 状态, 光照, 气压, 温度, 湿度, 粉尘, 紫外线) "
                           "values(?, ?, ?, ?, ?, ?, ?, ?)"));
    query.addBindValue(ui->label_time->text());
    query.addBindValue(ui->label_rs->text());
    query.addBindValue(ui->label_ilin->text());
    query.addBindValue(ui->label_aipr->text());
    query.addBindValue(ui->label_temp->text());
    query.addBindValue(ui->label_hum->text());
    query.addBindValue(ui->label_dust->text());
    query.addBindValue(ui->label_ulr->text());
    query.exec();

    MyDelay *delay = new MyDelay(3);
    connect(delay, SIGNAL(TimeOut()), this, SLOT(clearText()));
    ui->label_savestatus->setText(QObject::tr("保存成功"));
    delay->start();
}

void WeatherWidget::on_pushButton_Query_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("weather");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,250);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,50);
    ui->tableView->setColumnWidth(4,50);
    ui->tableView->setColumnWidth(5,50);
    ui->tableView->setColumnWidth(6,50);
    ui->tableView->setColumnWidth(7,70);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->stackedWidget->setCurrentIndex(1);
}

void WeatherWidget::on_pushButton_Close_clicked()
{
    emit closeCurrentPage();
}

void WeatherWidget::on_pushButton_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void WeatherWidget::getData(Data *data)
{
    if(data->rnsw == 0){
        ui->label->setStyleSheet("border-image: url(:/new/prefix1/res/weather-sensor/fine.png);");
        ui->label_rs->setText(QObject::tr("晴"));
    }
    else if(data->rnsw == 1){
        ui->label->setStyleSheet("border-image: url(:/new/prefix1/res/weather-sensor/rain.png);");
        ui->label_rs->setText(QObject::tr("雨"));
    }
    ui->label_temp->setNum(data->sht.a);
    ui->label_aipr->setText(QString::number(data->aipr,'f',2));
    ui->label_hum->setText(QString::number(data->sht.b,'f',2));
    ui->label_ilin->setText(QString::number(data->ilin,'f',2));
    ui->label_dust->setNum(data->dust);
    ui->label_ulr->setNum(data->ulr);
    if(data->dust==0)
        {
        ui->label_9->setText(QObject::tr("空气良好"));
        ui->label_notice->setText(QObject::tr("适宜外出，多出去走走，去呼吸新鲜空气吧！"));
        }
    else if(data->dust==0.1)
        {
        ui->label_9->setText(QObject::tr("中度污染"));
        ui->label_notice->setText(QObject::tr("减少外出，空气中的颗粒物对您有害！"));
        }
    else
        {
        ui->label_9->setText(QObject::tr("严重污染"));
        ui->label_notice->setText(QObject::tr("应该避免外出，敏感的人应该呆在室内，关闭门窗。"));
        }

}

void WeatherWidget::getCurTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString(QObject::tr("yyyy.MM.dd dddd(hh:mm:ss)实况"));
    ui->label_time->setText(str);
}

void WeatherWidget::clearText()
{
    ui->label_savestatus->setText("");
}
