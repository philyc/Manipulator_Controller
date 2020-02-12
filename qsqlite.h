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
    }robotData;   //sql接收到实时数据

    void initDB();
    void ExecAddSql(robotData stuInfo);

public slots:

    void closeDB(QSqlDatabase db);


signals:

};

#endif // QSQLITE_H
