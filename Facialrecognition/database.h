#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QSqlDatabase> //管理数据库连接的类
#include <QSqlQuery>    //执行sql语句
#include <QSqlError>      //输出错误信息
#include <QDebug>
#include <QCoreApplication>
#include "sign_up.h"

class database : public QWidget
{
    Q_OBJECT
public:
    explicit database(QWidget *parent = nullptr);
    QSqlDatabase db;    //管理数据库连接
    QSqlQuery *query;   //执行SQL语句
    ~database();

signals:

private slots:
//    void signup_signal_treat();

};

#endif // DATABASE_H
