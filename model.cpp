#include "model.h"


int flagRecAndInq=0;//0为初始关闭，1为打开，2为程序关闭——用于rec线程和inquire线程开关
bool flagAbsOrInc=false;
bool flagIsOpen=false;//减少线程启动时所进行的判断
bool flagDBOpen=false;
bool flag3DState=false;//倒立状态，test
bool flagDataRigth=false;//正常接收数据，使图表初始化时不产生突变
bool flagTest=false;
vector<double> absAngle(10,0);
vector<double> incAngle(10,0);
vector<double> current(10,0);
vector<double> absNum(10,0);//范围为-65536~65536
vector<double> incNum(10,0);//采用int可测试电机持续转268圈便溢出，改为long
DWORD devindex;//CAN设备索引
DWORD devtype;//CAN设备类型
UINT recIndex;
UINT sendIndex;
QString description="";
//QString sqlTableName;


Model::Model()
{

}
