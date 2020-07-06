#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "ControlCAN.h"
#include <vector>
#include <QtMath>


using namespace std;

extern int flagRecAndInq;//Rec线程和Inq线程启动与关闭
extern bool flagAbsOrInc;//绝对式编码器与相对式编码器切换，false为绝对式，true为相对式
extern bool flagIsOpen;//是否打开CAN
extern bool flagDBOpen;//数据库创建标志位
extern bool flag3DState;//三维显示状态
extern bool flagDataRigth;//图表初始化状态
extern bool flagTest;

extern vector<double> absAngle;//绝对式编码器值转化为角度
extern vector<double> incAngle;//相对式编码器值转化为角度
extern vector<double> current;//电流-预设
extern DWORD devindex;//CAN设备索引
extern DWORD devtype;//CAN设备类型
extern vector<double> absNum;//绝对式编码器值
extern vector<double> incNum;//相对式编码器值
extern UINT recIndex;//接收时电机序号，从0-5  //值= id-0x281
extern UINT sendIndex;//发送时电机序号，从0-5 //值= id-0x301
extern QString description;//实时状态
//extern QString sqlTableName;//数据库表名

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
    QString description;
}robotData;//sql接收到实时数据

typedef struct _poiData
{
    double pos_x;
    double pos_y;
    double pos_z;
    double cal_x;
    double cal_y;
    double cal_z;
    double dis=sqrt(pow((pos_x-cal_x),2)+pow((pos_y-cal_y),2)+pow((pos_z-cal_z),2));
}pointData;//正反解目标点数据

#define StandardFrame 0
#define ExpandFrame 1
#define DataFrame 0
#define RemoteFrame 1
#define CanDataLength 8
#define PI 3.14159265358979323846

#define Link1Length 120.0
#define Link2Length 264.0
#define Link3WLength 127.0
#define Link3HLength 213.0//定义为整数时，代入计算除法会出现错误
class Model: public QObject
{
    Q_OBJECT

public:
    Model();


public:

};

#endif // MODEL_H
