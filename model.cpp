#include "model.h"

int flagReceive=0;//0为初始关闭，1为打开，2为程序关闭
double absAngle[10];
double incAngle[10];
DWORD devindex;//CAN设备索引
DWORD devtype;//CAN设备类型

Model::Model()
{

}
