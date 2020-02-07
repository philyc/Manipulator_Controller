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


public slots:

    QString initDB(QSqlDatabase db);

    void closeDB(QSqlDatabase db);

    void execInsertSql(robotData recData,QString m_tablename,QSqlDatabase db);

};

#endif // QSQLITE_H
