#ifndef MODEL_H
#define MODEL_H

#include <QMainWindow>
#include <string>
#include "ControlCAN.h"
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


#define StandardFrame 0
#define ExpandFrame 1
#define DataFrame 0
#define RemoteFrame 1
#define CanDataLength 8

using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class Model; }
QT_END_NAMESPACE

class Model : public QMainWindow
{
    Q_OBJECT

public:
    Model(QWidget *parent = nullptr);
    ~Model();
    int Hex2Dec(char c);
    int DouHex2Dec(QString s);
    void CanSend();

public:
    DWORD devindex;//CAN设备索引
    DWORD devtype;//CAN设备类型
    VCI_CAN_OBJ sendbuf[1];//发送帧


private slots:
    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnSend_clicked();

    void on_BtnEnable_clicked();

private:
    Ui::Model *ui;
};
#endif // MODEL_H
