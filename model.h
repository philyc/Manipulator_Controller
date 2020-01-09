#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "ControlCAN.h"

extern int flagReceive;//线程启动与关闭
extern double absAngle[10];//绝对式编码器值转化为角度
extern double incAngle[10];//相对式编码器值转化为角度
extern DWORD devindex;//CAN设备索引
extern DWORD devtype;//CAN设备类型
extern int absNum[10];//绝对式编码器值
extern int incNum[10];//相对式编码器值

class Model: public QObject
{
    Q_OBJECT

public:
    Model();


public:
    double Angel[10];
};

#endif // MODEL_H
