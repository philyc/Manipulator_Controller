#ifndef VIEW_H
#define VIEW_H
#pragma once

#include <QMainWindow>
#include "controller.h"
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE



class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

public:
    Controller* m_controller;
    Model* m_model;

    QThread *receiveThread;

    int flag_temp=0;

signals:

    void open();
    void close();
    void send(QString Id,QString Data);
    void enable();
    void updateWindows(QString receiveId,QString receiveData);


public slots:


private slots:
    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnSend_clicked();

    void on_BtnEnable_clicked();

private:
    Ui::View *ui;

};
#endif // VIEW_H
