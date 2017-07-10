#include "database.h"
#include <QString>
#include <QDate>
#include <QTime>

DataBase::DataBase()
{

}
DataBase::~DataBase()
{

}

bool DataBase::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//qtDb.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}

bool DataBase::createConn()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//Records.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}


//创建数据库表
bool DataBase::createTb()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table cards(id varchar primary key,carNum varchar,readDate varchar,readTime varchar)");
    if(success)
    {
        qDebug() << QObject::tr("lyy: create DB SUCCESS！\n");

        //初始化一些记录
        for(int i=0;i<12;i++)
        {
            QString tmp=QObject::tr("%1").arg(i*3+1);
            insertToCards(tmp);
        }
        return true;
    }
    else
    {
        qDebug() << QObject::tr("lyy: create DB FAILED！\n");
        return false;
    }


}

//向数据库中插入记录
bool DataBase::insertToCards(QString cardNum)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接

//    QSqlQuery q(db);
    int recordNum;

    QSqlQuery query(db);
    query.prepare("select * from cards");
    if(query.exec()){
        int i=0;
        while(query.next()){
            i++;
        }
        recordNum=i;
        query.clear();
        qDebug()<<QObject::tr("lyy: recordsNumer---")<<recordNum;
    }else{
        qDebug()<<QObject::tr("lyy: select count ERROR.");
        return false;
    }
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy/MM/dd hh:mm:ss ddd");
    QString Date=current_date.left(10);


    QString Time= QTime::currentTime().toString();

    query.prepare(QString("insert into cards(id,carNum,readDate,readTime) values(?,?,?,?)"));

    query.bindValue(0,recordNum);
    query.bindValue(1,cardNum);
    query.bindValue(2,Date);
    query.bindValue(3,Time);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("lyy: insert into table FAILED!"));
        return false;
    }
    qDebug() << QString(QObject::tr("lyy: insert to table SUCCESS!"));
    return true;
}

//根据
int DataBase::queryCountsAccordingCardNumAndTime(QString cardNum, QString readDate)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("select * from cards where carNum= ? and readDate= ?");
    query.bindValue(0,cardNum);
    query.bindValue(1,readDate);
    query.exec();
    int count=0;
    while(query.next())
    {
        count++;
    }
//    qDebug()<<QObject::tr("lyy:flow")<<count;
    return count;
}

//查询所有信息
bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from cards");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("lyy:cards tables column Number：" ) << rec.count();

    while(query.next())
    {
        for(int index = 0; index < rec.count(); index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
}

//根据ID删除记录
bool DataBase::deleteById()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("delete * from cards");
    if(!query.exec())
    {
        qDebug() << "lyy: delete table FAILED！";
        return false;
    }
    return true;
}

//根据ID更新记录
bool DataBase::updateById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("update automobil set attribute=?,type=?,"
                             "kind=?, nation=?,"
                             "carnumber=?, elevaltor=?,"
                             "distance=?, oil=?,"
                             "temperature=? where id=%1").arg(id));

     query.bindValue(0,"四轮");
     query.bindValue(1,"轿车");
     query.bindValue(2,"富康");
     query.bindValue(3,rand()%100);
     query.bindValue(4,rand()%10000);
     query.bindValue(5,rand()%300);
     query.bindValue(6,rand()%200000);
     query.bindValue(7,rand()%52);
     query.bindValue(8,rand()%100);

     bool success=query.exec();
     if(!success)
     {
          QSqlError lastError = query.lastError();
          qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
     }
    return true;
}

//排序
bool DataBase::sortById()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("select * from automobil order by id desc");
    if(success)
    {
        qDebug() << QObject::tr("排序成功");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("排序失败！");
        return false;
    }
}
