#ifndef QSQLITE_H
#define QSQLITE_H

#include <QObject>
#include "model.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QDateTime>

class QSqlite: public QObject
{
    Q_OBJECT
public:
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
    }robotData;

    QString tableName;

public:
    QSqlite();

public slots:

    QString initDB();


};

#endif // QSQLITE_H
