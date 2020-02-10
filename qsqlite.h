#ifndef QSQLITE_H
#define QSQLITE_H

#include <QObject>
#include "model.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QSqlError>

class QSqlite: public QObject
{
    Q_OBJECT
public:

    QString tableName;
    QSqlDatabase db;

public:
    QSqlite();


//    QString initDB2();
//    int m_name=100;
//    int m_phone=200;
//    int m_email=300;
//    int m_address=400;
//    int m_description=500;

//    typedef struct _test
//    {
//        QString create_date;
//        QString name;
//        QString phone;
//        QString email;
//        QString address;
//        QString description;
//    }testInfo;

    typedef struct _robData
    {
        QString time;
        QString moter1angle;
        QString moter1current;
        QString moter2angle;
        QString moter2current;
        QString moter3angle;
        QString moter3current;
        QString moter4angle;
        QString moter4current;
        QString moter5angle;
        QString moter5current;
        QString moter6angle;
        QString moter6current;
        QString description;
    }robotData;//sql接收到实时数据

    void initDB2();
    void ExecAddSql2(robotData stuInfo);
//    testInfo stuInfo;


public slots:

//    void execSql(robotData recData);

//    QString initDB(QSqlDatabase db);

    void closeDB(QSqlDatabase db);

//    void execInsertSql(robotData recData,QString m_tablename,QSqlDatabase db);

signals:
//    void changeDbSta();

};

#endif // QSQLITE_H
