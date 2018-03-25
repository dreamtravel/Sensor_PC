/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is the main interface class of Sensor platform system software.
**
*****************************************************************************/

#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    stackedWidgetInit();//界面填充
    ui->stackedWidget->setCurrentIndex(0);

    data = new Data();
    dataAnalysis = new DataAnalysis();
    dataAnalysis->COMOpen();
    dataAnalysis->start();

    updateThread = new UpdateThread();
    updateThread->start();
    //QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);

    connect(updateThread, SIGNAL(TimeOut()), data, SLOT(dataReceive()));
    connect(updateThread, SIGNAL(TimeOut()), this, SLOT(sendData()));
    connect(this, SIGNAL(allSensorInfo(Data*)), allSensorWidget, SLOT(getData(Data*)));
    connect(this, SIGNAL(allSensorInfo(Data*)), multimeterWidget, SLOT(getData(Data*)));
    connect(this, SIGNAL(allSensorInfo(Data*)), navigateWidget, SLOT(getData(Data*)));
    connect(this, SIGNAL(allSensorInfo(Data*)), securityWidget, SLOT(getData(Data*)));
    connect(this, SIGNAL(allSensorInfo(Data*)), weatherWidget, SLOT(getData(Data*)));

}

MainWidget::~MainWidget()
{
    delete ui;
}

/*
 *函数名:on_pushButton_AllSensor_clicked
 *函数功能描述:传感器信息界面切换
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::on_pushButton_AllSensor_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/*
 *函数名:on_pushButton_Security_clicked
 *函数功能描述:安防界面切换
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::on_pushButton_Security_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/*
 *函数名:on_pushButton_Weather_clicked
 *函数功能描述:天气界面切换
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::on_pushButton_Weather_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/*
 *函数名:on_pushButton_Navigate_clicked
 *函数功能描述:导航界面切换
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::on_pushButton_Navigate_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/*
 *函数名:on_pushButton_Multimeter_clicked
 *函数功能描述:万用表界面切换
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::on_pushButton_Multimeter_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

/*
 *函数名:changeToMainPage
 *函数功能描述:返回主界面
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::changeToMainPage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::sendData()
{
    emit allSensorInfo(data);
}
/*
 *函数名:stackedWidgetInit
 *函数功能描述:主界面stackedWidget控件填充
 *函数参数:无
 *函数返回值:无
 */
void MainWidget::stackedWidgetInit()
{
    allSensorWidget = new AllSensorWidget(this);
    securityWidget = new SecurityWidget(this);
    weatherWidget = new WeatherWidget(this);
    multimeterWidget = new MultimeterWidget(this);
    navigateWidget = new NavigateWidget(this);
    ui->stackedWidget->addWidget(allSensorWidget);
    ui->stackedWidget->addWidget(securityWidget);
    ui->stackedWidget->addWidget(weatherWidget);
    ui->stackedWidget->addWidget(navigateWidget);
    ui->stackedWidget->addWidget(multimeterWidget);

    //响应子界面关闭信号
    connect(allSensorWidget, SIGNAL(closeCurrentPage()), this, SLOT(changeToMainPage()));
    connect(securityWidget, SIGNAL(closeCurrentPage()), this, SLOT(changeToMainPage()));
    connect(weatherWidget, SIGNAL(closeCurrentPage()), this, SLOT(changeToMainPage()));
    connect(navigateWidget, SIGNAL(closeCurrentPage()), this, SLOT(changeToMainPage()));
    connect(multimeterWidget, SIGNAL(closeCurrentPage()), this, SLOT(changeToMainPage()));

    ui->pushButton_AllSensor->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/lanse_01.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/lanse_01.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/huise_01.png);}");
    ui->pushButton_Security->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/lanse_02.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/lanse_02.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/huise_02.png);}");
    ui->pushButton_Weather->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/lanse_03.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/lanse_03.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/huise_03.png);}");
    ui->pushButton_Navigate->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/lanse_04.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/lanse_04.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/huise_04.png);}");
    ui->pushButton_Multimeter->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/res/main/lanse_05.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/res/main/lanse_05.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/res/main/huise_05.png);}");
}

void MainWidget::on_setBtn_clicked()
{
    QString port=ui->cmboxcom->currentText();
    QString str=ui->cmboxbaud->currentText();
    //str.insert(0,"B");
    BaudRateType baud=(BaudRateType)str.toInt();
    qDebug()<<port<<"-----"<<baud;
    dataAnalysis->stop();
    dataAnalysis->setPort(port,baud);
}
