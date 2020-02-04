#ifndef QSQLITE_H
#define QSQLITE_H

#include <QObject>
#include "model.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class qsqlite: public QObject
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

public:
    qsqlite();



};

#endif // QSQLITE_H
