#include "model.h"

int flagRecAndInq=0;//0为初始关闭，1为打开，2为程序关闭——用于rec线程和inquire线程开关
bool flagAbsOrInc=false;
vector<double> absAngle(10,0);
vector<double> incAngle(10,0);
vector<int> absNum(10,0);
vector<int> incNum(10,0);
DWORD devindex;//CAN设备索引
DWORD devtype;//CAN设备类型
UINT recIndex;
UINT sendIndex;


Model::Model()
{

}
