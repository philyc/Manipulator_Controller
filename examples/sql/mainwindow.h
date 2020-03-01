#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int m_name=100;
    int m_phone=200;
    int m_email=300;
    int m_address=400;
    int m_description=500;


    typedef struct _test
    {
        QString create_date;
        QString name;
        QString phone;
        QString email;
        QString address;
        QString description;
    }testInfo;

    QString initDB();
    void ExecAddSql(testInfo stuInfo);

    testInfo stuInfo;
    QString tableName;



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
