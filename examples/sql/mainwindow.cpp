#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initDB();
    ExecAddSql(stuInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");//设置主机名
    db.setDatabaseName("AddressBook.db");
    //db.setUserName("root");   // 如果是 SQLite 不需要
    //db.setPassword("root");   // 如果是 SQLite 不需要
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";

        QSqlQuery query;
        tableName=QDateTime::currentDateTime().toString(("yyyy-MM-dd hh:mm:ss"));
        QString createTable=QString("create table '%1' (create_date datetime, "
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "name varchar(20) ,"
                                    "phone varchar(20), "
                                    "email varchar(20) , "
                                    "address varchar(20) ,"
                                    " description varchar(50),"
                                    "test varchar(20))")
                .arg(tableName);
//        query.exec("create table FriendManager (create_date datetime, "
//                   "id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(20) ,phone varchar(20), "
//                   "email varchar(20) , address varchar(20) , description varchar(50))");
        query.exec(createTable);
        return tableName;
    }
    else
    {
        qDebug()<<"open failed"<<db.databaseName();
        return "";
    }
}

void MainWindow::ExecAddSql(testInfo stuInfo)
{
    stuInfo.create_date=QDateTime::currentDateTime().toString(("yyyy-MM-dd hh:mm::ss.zzz"));
    stuInfo.phone = QString("%1").arg(m_phone);
    stuInfo.name = QString("%1").arg(m_name);
    stuInfo.email = QString("%1").arg(m_email);
    stuInfo.address = QString("%1").arg(m_address);
    stuInfo.description = QString("%1").arg(m_description);
//    QString phone = stuInfo.value("phone").toString();
//    QString name = stuInfo.value("name").toString();
//    QString email = stuInfo.value("email").toString();
//    QString address = stuInfo.value("address").toString();
//    QString description = stuInfo.value("desc").toString();

    QString sql;
    sql = QString("insert into '%7' (create_date,name ,phone ,email ,address , description)"
                  " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6')")
            .arg(stuInfo.create_date).arg(stuInfo.name).arg(stuInfo.phone).arg(stuInfo.email).arg(stuInfo.address).arg(stuInfo.description).arg(tableName);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
        QStringList rowData;
        rowData << stuInfo.name <<stuInfo.phone <<stuInfo.email << stuInfo.address << stuInfo.description ;
        qDebug()<<"add success!";
    }
    else
    {
        qDebug()<<"add failed!";
    }
}

