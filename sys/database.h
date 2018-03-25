/*****************************************************************************
**
**Copyright (C) 2014 UP-TECH Corporation and/or its subsidiary(-ies).
**All rights reserved.
**Contact: UP-TECH Corporation (anld@up-tech.com)
**
**This file is part of the Database Toolkit.
**
*****************************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>

/*
 *函数名:initDatabase
 *函数功能描述:系统数据库初始化
 *函数参数:无
 *函数返回值:true-成功  false-失败
 */
static bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(!db.open()) return false;

    QSqlQuery query;
    query.exec(QObject::tr("create table door (时间 vchar primary key, 类型 vchar, 状态 vchar)"));
    query.exec(QObject::tr("create table window (时间 vchar primary key, 类型 vchar, 状态 vchar)"));
    query.exec(QObject::tr("create table kitchen (时间 vchar primary key, 类型 vchar, 状态 vchar)"));
    query.exec(QObject::tr("create table carport (时间 vchar primary key, 类型 vchar, 状态 vchar)"));
    query.exec(QObject::tr("create table weather (时间 vchar primary key, 状态 vchar, 光照 vchar, 气压 vchar, 温度 vchar, 湿度 vchar, 粉尘 vchar, 紫外线 vchar)"));

    return true;
}

#endif // DATABASE_H
