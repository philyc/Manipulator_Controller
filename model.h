#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "ControlCAN.h"
#include <vector>

using namespace std;

extern int flagRecAndInq;//Rec线程和Inq线程启动与关闭
extern bool flagAbsOrInc;//绝对式编码器与相对式编码器切换，false为绝对式，true为相对式
extern vector<double> absAngle;//绝对式编码器值转化为角度
extern vector<double> incAngle;//相对式编码器值转化为角度
extern DWORD devindex;//CAN设备索引
extern DWORD devtype;//CAN设备类型
extern vector<int> absNum;//绝对式编码器值
extern vector<int> incNum;//相对式编码器值
extern UINT recIndex;//接收时电机序号，从0-5  //值= id-0x281
extern UINT sendIndex;//发送是电机序号，从0-5 //值= id-0x301

class Model: public QObject
{
    Q_OBJECT

public:
    Model();


public:

};

#endif // MODEL_H
