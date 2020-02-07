#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "ControlCAN.h"
#include <QMainWindow>
#include <string>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QtMath>
#include <QMessageBox>
#include <synchapi.h>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QThread>
#include <QTimer>
#include "model.h"
#include "qsqlite.h"

#define StandardFrame 0
#define ExpandFrame 1
#define DataFrame 0
#define RemoteFrame 1
#define CanDataLength 8
#define PI 3.1415926

using namespace std;


class Controller: public QObject
{
    Q_OBJECT

public:
    Controller();
    int DouHex2Dec(QString s);
    int Hex2Dec(char c);
    void CanSend();

    void MoterRunFor(UINT index,QString angle);
    void MoterRunRev(UINT index,QString angle);

public:
    //    DWORD devindex;//CAN设备索引
    //    DWORD devtype;//CAN设备类型
    VCI_CAN_OBJ sendbuf[1];//发送帧

    UINT ReceiveId;//receive线程中收到的id
    BYTE ReceiveData[8];//receive线程中收到的data


signals:
    void rec(QString receiveId,QString receiveData);

    void recAbsAngle(vector<double> absAngle);

    void recIncNum(vector<long> incNum);

    void insertSql(robotData recData,QString m_tablename);


public slots:
    void btnOpenClick();
    void btnCloseClick();
    void btnSendClick(QString Id,QString Data);
    void btnEnableClick();

    void btnMoterRunClick(bool isForward,UINT index,QString angle);


    void receive();
    void inquire();

};

#endif // CONTROLLER_H
