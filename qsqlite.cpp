#include "qsqlite.h"

QSqlite::QSqlite()
{

}


QString QSqlite::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");//设置主机名
    db.setDatabaseName("RobData.db");
    //db.setUserName("root");   // 如果是 SQLite 不需要
    //db.setPassword("root");   // 如果是 SQLite 不需要
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";
        QSqlQuery query;
        QString tableName=QDateTime::currentDateTime().toString(("yyyy-MM-dd hh:mm:ss"));
        QString createTable=QString("create table '%1' (create_date datetime, "
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
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
                                    " description varchar(50))")
                .arg(tableName);
        query.exec(createTable);
        return tableName;
    }
    else
    {
        qDebug()<<"open failed"<<db.databaseName();
        return "";
    }
}
