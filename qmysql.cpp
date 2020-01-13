#include "qmysql.h"

bool sqlconnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");       //数据库名
    db.setUserName("root");
    db.setPassword("password123");
    if (!db.open())
    {
        qDebug()<<"Connect SQL fail";
        return false;
    }
    else qDebug()<<"Connect SQL success!";

    QSqlQuery test1(db);



    test1.exec("SET NAMES 'Latin1'");    // 使数据库支持中文


    test1.exec("create table data (id int primary key, time varchar(20), angle varchar(20))");

    return true;
}
