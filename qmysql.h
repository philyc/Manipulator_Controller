#ifndef QMYSQL_H
#define QMYSQL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include "model.h"

extern QSqlDatabase db;



bool sqlconnect();

QDateTime now=QDateTime::currentDateTime();



//QTime timenow;


#endif // QMYSQL_H
