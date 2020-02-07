#include "qsqlite.h"

QSqlite::QSqlite()
{

}


QString QSqlite::initDB(QSqlDatabase db)
{
    if(QSqlDatabase::contains("Rob"))
    {
        db=QSqlDatabase::database("Rob");//去除多次连接出现duplicate_connection错误
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE","Rob");
    }
    //db.setHostName("localhost");//设置主机名
    db.setDatabaseName("RobData.db");
    //db.setUserName("root");   // 如果是 SQLite 不需要
    //db.setPassword("root");   // 如果是 SQLite 不需要
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";
        tableName=QDateTime::currentDateTime().toString(("yyyy-MM-dd hh:mm:ss"));
        QString createTable=QString("create table '%1' "
                                    "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "create_date datetime,"
                                    "moter1angle varchar(20),"
                                    "moter1current varchar(20),"
                                    "moter2angle varchar(20),"
                                    "moter2current varchar(20),"
                                    "moter3angle varchar(20),"
                                    "moter3current varchar(20),"
                                    "moter4angle varchar(20),"
                                    "moter4current varchar(20),"
                                    "moter5angle varchar(20),"
                                    "moter5current varchar(20),"
                                    "moter6angle varchar(20),"
                                    "moter7current varchar(20),"
                                    "description varchar(50))")
                .arg(tableName);
        QSqlQuery query(createTable,db);
//        query.exec(createTable,db);
        return tableName;
    }
    else
    {
        qDebug()<<"open failed"<<db.databaseName()<<"error-"<<db.lastError();
        return "";
    }
}

void QSqlite::execInsertSql(robotData recData, QString m_tablename,QSqlDatabase db)
{
    if(tableName=="") return;
    else{
        recData.time=QDateTime::currentDateTime().toString(("yyyy-MM-dd hh:mm:ss"));
        recData.moter1angle=QString("%1").arg(absAngle[0]);
        recData.moter2angle=QString("%1").arg(absAngle[1]);
        recData.moter3angle=QString("%1").arg(absAngle[2]);
        recData.moter4angle=QString("%1").arg(absAngle[3]);
        recData.moter5angle=QString("%1").arg(absAngle[4]);
        recData.moter6angle=QString("%1").arg(absAngle[5]);
        recData.description=description;

        QString sql_insert;
        sql_insert=QString("insert into '%1' (create_date,moter1angle,moter1current,moter2angle,moter2current,moter3angle,moter3current,moter4angle,moter4current,moter5angle,moter5current,moter6angle,moter6current,description)"
                           " VALUES ('%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15')")
                .arg(m_tablename).arg(recData.time).arg(recData.moter1angle).arg(recData.moter1current).arg(recData.moter2angle).arg(recData.moter2current).arg(recData.moter3angle).arg(recData.moter3current).arg(recData.moter4angle).arg(recData.moter4current).arg(recData.moter5angle).arg(recData.moter5current).arg(recData.moter6angle).arg(recData.moter6current).arg(recData.description);

        QSqlQuery query=QSqlQuery(db);
        bool ok=query.exec(sql_insert);
        if(ok)
        {
            qDebug()<<"insert success";
        }
        else
        {
            qDebug()<<"insert fail";
        }
    }

}

void QSqlite::closeDB(QSqlDatabase db)
{
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");
    qDebug()<<"Close DB";
}

