#ifndef VIEW_H
#define VIEW_H
#pragma once

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include "controller.h"
#include "model.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE



class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);

    void widgetshow(QCustomPlot *widget,int recIndex);

    ~View();

public:
    Controller* m_receiver;//receive线程对应的QObject
    Controller* m_inquirer;//inquire线程对应的QObject
    Controller* m_controller;//其他引用函数

    Model* m_model;

    QThread *receiveThread;
    QThread *inquireThread;


signals:

    void open();
    void close();
    void send(QString Id,QString Data);
    void enable();



public slots:


private slots:
    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnSend_clicked();

    void on_BtnEnable_clicked();

    void updateTest(QString receiveId,QString receiveData);

    void updateAbsAngle(vector<double> absAngle);

    void updateIncNum(vector<long> incNum);

    void timeUpdate();

private:
    Ui::View *ui;

};
#endif // VIEW_H
