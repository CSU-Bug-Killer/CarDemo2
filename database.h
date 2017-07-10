#ifndef DATABASE_H
#define DATABASE_H

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>


class DataBase
{
public:
    DataBase();
    ~DataBase();
    bool createConnection();  //创建一个连接
//    bool createTable();       //创建数据库表
    bool insert();            //出入数据
    bool queryAll();          //查询所有信息
    bool updateById(int id);  //更新
    bool deleteById();  //删除
    bool sortById();          //排序


    //我的代码
    bool createConn();  //创建一个连接
    bool createTb();       //创建数据库表
    bool insertToCards(QString cardNum);            //插入数据
    int queryCountsAccordingCardNumAndTime(QString cardNum , QString readDate);          //查询所有信息

private:

};

#endif // DATABASE_H
