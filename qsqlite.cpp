#include "qsqlite.h"

QSqlite::QSqlite()
{

}

void QSqlite::closeDB(QSqlDatabase db)
{
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");
    qDebug()<<"Close DB";
}


void QSqlite::initDB()
{
//    if(QSqlDatabase::contains("Rob"))
//    {
//        db=QSqlDatabase::database("Rob");//去除多次连接出现duplicate_connection错误
//    }
//    else
//    {
//        db = QSqlDatabase::addDatabase("QSQLITE","Rob");
//    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");//设置主机名
    db.setDatabaseName("ManipulatorData.db");//数据库文件名
    //db.setUserName("root");   // 如果是 SQLite 不需要
    //db.setPassword("root");   // 如果是 SQLite 不需要
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";

        QSqlQuery query;
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
                                    "moter6current varchar(20),"
                                    "description varchar(50))")
                .arg(tableName);
        query.exec(createTable);
        return ;
    }
    else
    {
        qDebug()<<"open failed"<<db.databaseName();
        return ;
    }
}

void QSqlite::ExecAddSql(robotData recData)
{
//    recData.time=QDateTime::currentDateTime().toString(("hh:mm:ss.z"));
//    switch (recIndex) {
//    case 0:
//        recData.moter1angle=QString("%1").arg(absAngle[0]);
//        //    recData.moter1current=QString("%1").arg(current[0]);
//        break;//1号电机
//    case 1:
//        recData.moter2angle=QString("%1").arg(absAngle[1]);
//        //    recData.moter2current=QString("%1").arg(current[1]);
//        break;//2号电机
//    case 2:
//        recData.moter3angle=QString("%1").arg(absAngle[2]);
//        //    recData.moter3current=QString("%1").arg(current[2]);
//        break;//3号电机
//    case 3:
//        recData.moter4angle=QString("%1").arg(absAngle[3]);
//        //    recData.moter4current=QString("%1").arg(current[3]);
//        break;//4号电机
//    case 4:
//        recData.moter5angle=QString("%1").arg(absAngle[4]);
//        //    recData.moter5current=QString("%1").arg(current[4]);
//        break;//5号电机
//    case 5:
//        recData.moter6angle=QString("%1").arg(absAngle[5]);
//        //    recData.moter6current=QString("%1").arg(current[5]);
//        break;//6号电机
//    default:break;
//    }
//    recData.description=description;

//    recData.time=QDateTime::currentDateTime().toString(("hh:mm:ss.z"));
//    recData.moter1angle=QString("%1").arg(absAngle[0]);//以绝对值传感器反馈值为标准
//    recData.moter1current=QString("%1").arg(current[0]);
//    recData.moter2angle=QString("%1").arg(absAngle[1]);
//    recData.moter2current=QString("%1").arg(current[1]);
//    recData.moter3angle=QString("%1").arg(absAngle[2]);
//    recData.moter3current=QString("%1").arg(current[2]);
//    recData.moter4angle=QString("%1").arg(absAngle[3]);
//    recData.moter4current=QString("%1").arg(current[3]);
//    recData.moter5angle=QString("%1").arg(absAngle[4]);
//    recData.moter5current=QString("%1").arg(current[4]);
//    recData.moter6angle=QString("%1").arg(absAngle[5]);
//    recData.moter6current=QString("%1").arg(current[5]);
//    recData.description=description;

    QString sql;

    sql=QString("insert into '%15' "
                "(create_date,"
                "moter1angle,"
                "moter1current,"
                "moter2angle,"
                "moter2current,"
                "moter3angle,"
                "moter3current,"
                "moter4angle,"
                "moter4current,"
                "moter5angle,"
                "moter5current,"
                "moter6angle,"
                "moter6current,"
                "description)"
                " VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14')")
            .arg(recData.time)
            .arg(recData.moter1angle)
            .arg(recData.moter1current)
            .arg(recData.moter2angle)
            .arg(recData.moter2current)
            .arg(recData.moter3angle)
            .arg(recData.moter3current)
            .arg(recData.moter4angle)
            .arg(recData.moter4current)
            .arg(recData.moter5angle)
            .arg(recData.moter5current)
            .arg(recData.moter6angle)
            .arg(recData.moter6current)
            .arg(recData.description)
            .arg(tableName);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
//        qDebug()<<"add success!";
    }
    else
    {
        qDebug()<<"add failed!"<<db.databaseName()<<db.lastError();
    }
}

