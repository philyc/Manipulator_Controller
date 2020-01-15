#include "model.h"


int flagRecAndInq=0;//0为初始关闭，1为打开，2为程序关闭——用于rec线程和inquire线程开关
bool flagAbsOrInc=false;
bool flagIsOpen=false;
vector<double> absAngle(10,0);
vector<double> incAngle(10,0);
vector<int> absNum(10,0);//范围为-65536~65536
vector<long> incNum(10,0);//采用int可测试电机持续转268圈便溢出，改为long
DWORD devindex;//CAN设备索引
DWORD devtype;//CAN设备类型
UINT recIndex;
UINT sendIndex;


Model::Model()
{

}
