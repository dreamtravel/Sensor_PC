#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T09:18:25
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SensorPlatform
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    serial/dataanalysis.cpp \
    tool/datacalculate.cpp \
    case/weatherwidget.cpp \
    case/securitywidget.cpp \
    case/navigatewidget.cpp \
    case/multimeterwidget.cpp \
    case/allsensorwidget.cpp \
    serial/data.cpp \
    tool/updatethread.cpp \
    tool/mydelay.cpp \
    serial/qextserialbase.cpp \
    serial/qextserialport.cpp \
    serial/win_qextserialport.cpp

HEADERS  += mainwidget.h \
    cmd/sensorprotocol.h \
    serial/dataanalysis.h \
    sys/sysinfo.h \
    tool/datacalculate.h \
    case/weatherwidget.h \
    case/securitywidget.h \
    case/navigatewidget.h \
    case/multimeterwidget.h \
    sys/database.h \
    case/allsensorwidget.h \
    serial/data.h \
    tool/updatethread.h \
    tool/mydelay.h \
    serial/qextserialbase.h \
    serial/qextserialport.h \
    serial/win_qextserialport.h

FORMS    += mainwidget.ui \
    case/weatherwidget.ui \
    case/securitywidget.ui \
    case/navigatewidget.ui \
    case/multimeterwidget.ui \
    case/allsensorwidget.ui

RESOURCES += \
    res.qrc
