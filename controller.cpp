#include "controller.h"
#include "view.h"



Controller::Controller()
{
    sendbuf->ExternFlag=StandardFrame;//CAN帧初始化，ID为标准帧
    sendbuf->DataLen=static_cast<BYTE>(CanDataLength);//数据长度为8位
    sendbuf->RemoteFlag=DataFrame;//DATA为数据帧
    for(int i=0;i<8;++i){
        sendbuf->Data[i]=0x00;//DATA数据默认为0x00
    }
    InitializeCriticalSection(&send_syn);
}


void Controller::btnOpenClick()
{
    devindex=0;//开启第一个CAN适配器
    int Doublechoose=1;
    devtype=Doublechoose==1?VCI_USBCAN2:VCI_USBCAN1;//设备类型为CANalyst-II
    DWORD reserved=0;

    if(VCI_OpenDevice(devtype,devindex,reserved)!=1){
        //        QMessageBox::warning(this,QString::fromLocal8Bit("Warning"),
        //                                 QString::fromLocal8Bit("Open Device failed!"));
        qDebug()<<"Open Device failed!";
        return;
    }
    VCI_INIT_CONFIG init_info[1];
    init_info->Timing0=0x00;
    init_info->Timing1=0x14;//波特率设为1M
    init_info->Filter=0;//同时对标准帧和拓展帧进行过滤
    init_info->AccCode=0x80000008;
    init_info->AccMask=0xFFFFFFFF;//接收所有消息
    init_info->Mode=0;//工作模式为正常工作模式

    if(VCI_InitCAN(devtype,devindex,0,init_info)!=1)//初始化通道0
    {
        //        QMessageBox::warning(this,QString::fromLocal8Bit("Warning"),
        //                                 QString::fromLocal8Bit("CAN init failed!"));
        qDebug()<<"CAN init failed!";
        return;
    }
    Sleep(10);
    if(VCI_StartCAN(devtype,devindex,0)!=1)//开启通道0
    {
        //        QMessageBox::warning(this,QString::fromLocal8Bit("Warning"),
        //                                 QString::fromLocal8Bit("Start CAN failed!"));
        qDebug()<<"Start CAN failed!";
        return;
    }
    qDebug()<<"Open CAN success!";
    flagIsOpen=true;
    return;
}


void Controller::btnCloseClick()
{
    if(VCI_CloseDevice(devtype,devindex)!=1)
    {
        //        QMessageBox::warning(this,QString::fromLocal8Bit("Warning"),
        //                                 QString::fromLocal8Bit("Close failed!"));
        qDebug()<<"Close failed!";
        return;
    }

    //    QMessageBox::information(this,QString::fromLocal8Bit("Information"),
    //                             QString::fromLocal8Bit("Close success!"));
    qDebug()<<"Close success!";
    flagIsOpen=false;
}

int Controller::Hex2Dec(char c)
{
    if((c>='0') && (c<='9'))
        return c-0x30;
    else if((c>='A') && (c<='F'))
        return c-'A'+10;
    else if((c>='a') && (c<='f'))
        return c-'a'+10;
    else
        return 0x10;
}

int Controller::DouHex2Dec(QString s)
{
    int len=s.length();
    string str=s.toStdString();
    if(len==2)
    {
        int a=Hex2Dec(str[0]);
        int b=Hex2Dec(str[1]);
        if(a==16||b==16)
        {
            qDebug()<<"Format error";
            return 256;
        }
        else
        {
            return a*16+b;
        }
    }
    else
    {
        qDebug()<<"input length must be 2";
        return 256;
    }
}

void Controller::btnSendClick(QString Id,QString Data)
{
    QString str5[32];
    BYTE databuf[50];
    BYTE idbuf[10];
    QString strtemp,strtemp1;
    QString str;
    int len,datanum=0,idnum=0,flag=1,i;
    QString qstr_id=Id;
    QString qstr_data=Data;

    len=qstr_id.length();
    for(i=0;i<len;++i)
    {
        strtemp=qstr_id.at(i);
        if(strtemp==" ")
            flag=1;
        else if(flag==1)
        {
            flag=0;
            strtemp=qstr_id.at(i);
            if(i==(len-1))
            {
                str5[idnum]="0"+strtemp;
            }
            else
            {
                strtemp1=qstr_id.at(i+1);
                if(strtemp1==" ")
                    str5[idnum]="0"+strtemp;
                else
                    str5[idnum]=strtemp+strtemp1;
            }
            idbuf[idnum]=static_cast<BYTE>(DouHex2Dec(str5[idnum]));
            idnum++;
            if(idnum>=4)
                break;
        }
    }

    flag=1;
    len=qstr_data.length();
    for(i=0;i<len;++i)
    {
        strtemp=qstr_data.at(i);
        if(strtemp==" ")
            flag=1;
        else if(flag==1)
        {
            flag=0;
            strtemp=qstr_data.at(i);
            if(i==(len-1))
            {
                str5[datanum]="0"+strtemp;
            }
            else
            {
                strtemp1=qstr_data.at(i+1);
                if(strtemp1==" ")
                    str5[datanum]="0"+strtemp;
                else
                    str5[datanum]=strtemp+strtemp1;
            }
            databuf[datanum]=static_cast<BYTE>(DouHex2Dec(str5[datanum]));
            datanum++;
            if(datanum>=8)
                break;
        }
    }
    sendbuf->ID=static_cast<UINT>(idbuf[0]*pow(16,6)+idbuf[1]*pow(16,4)+idbuf[2]*pow(16,2)+idbuf[3]);
    for(i=0;i<datanum;++i)
    {
        sendbuf->Data[i]=databuf[i];
    }

    CanSend();
}

void Controller::CanSend()
{
    if(flagRecAndInq==1)
    {
        EnterCriticalSection(&send_syn);
        int NumCanSend=static_cast<int>(VCI_Transmit(devtype,devindex,static_cast<DWORD>(0),sendbuf,1));
        if(NumCanSend<1){
            switch (NumCanSend) {
            case -1:qDebug()<<"Device isn't open";
                LeaveCriticalSection(&send_syn);return;
                //        case 0:qDebug()<<"send error";return;
            default:
                LeaveCriticalSection(&send_syn);return;
            }
        }
        //    qDebug()<<"Cansend success"<<sendbuf->ID<<" "<<sendbuf->Data[0];
        //重新初始化sendbuf
        sendbuf->ExternFlag=StandardFrame;//CAN帧初始化，ID为标准帧
        sendbuf->DataLen=static_cast<BYTE>(CanDataLength);//数据长度为8位
        sendbuf->RemoteFlag=DataFrame;//DATA为数据帧
        for(int i=0;i<8;++i){
            sendbuf->Data[i]=0x00;//DATA数据默认为0x00
        }
        LeaveCriticalSection(&send_syn);
    }
    else return;
}

void Controller::btnEnableClick()
{
    sendbuf->ID=0x00000302;
    sendbuf->Data[0]=0x4D;
    sendbuf->Data[1]=0x4F;
    sendbuf->Data[4]=0x01;
    CanSend();
    Sleep(50);

    sendbuf->ID=0x00000303;
    sendbuf->Data[0]=0x4D;
    sendbuf->Data[1]=0x4F;
    sendbuf->Data[4]=0x01;
    CanSend();
    Sleep(50);

    sendbuf->ID=0x00000304;
    sendbuf->Data[0]=0x4D;
    sendbuf->Data[1]=0x4F;
    sendbuf->Data[4]=0x01;
    CanSend();
    Sleep(50);
}

void Controller::inquire()
{
    while(flagRecAndInq)
    {
        flagAbsOrInc=false;
        for(UINT i=1;i<7;++i)
        {
            sendbuf->ID=0x0000300+i;
            sendbuf->Data[0]=0x41;
            sendbuf->Data[1]=0x45;
            sendbuf->Data[2]=0x01;
            CanSend();
            Sleep(50);//Sleep不得低于50，否则处理不过来
        }
//        flagAbsOrInc=true;
//        for(UINT i=1;i<7;++i)
//        {
//            sendbuf->ID=0x300+i;
//            sendbuf->Data[0]=0x50;
//            sendbuf->Data[1]=0x58;
//            CanSend();
//            Sleep(50);
//        }

//        Sleep(50);
//        qDebug()<<"Inquire rest";
        //        QString log;
        //        log.sprintf("%p",QThread::currentThread());
        //        qDebug()<<"testinquire"<<++i<<log;
        if(flagRecAndInq==2)
        {
            return;
        }
    }
}


void Controller::receive()
{
    //    int i=0;
    QSqlite *m_sqlite2=new QSqlite();
    int count=0;//收到角度反馈消息计数
    VCI_CAN_OBJ pCanObj[200];
    while(flagRecAndInq)
    {
        if(flagRecAndInq==2)
        {
            delete m_sqlite2;
            return;
        }
        int NumCanReceive;
        QString strRecId,strRecData,str;
//        VCI_CAN_OBJ pCanObj[200];
        NumCanReceive=static_cast<int>(VCI_Receive(devtype,devindex,0,pCanObj,200,0));

//        //数据库插入--暂调试使用
//        if(flagDBOpen==false){
//            m_sqlite2->initDB();

//            flagDBOpen=true;
//        }
//        else
//        {
//            QSqlite::robotData s;
//            m_sqlite2->ExecAddSql(s);
//        }


        //正解更新--暂调试使用
        vector<double> leftAngle;
        vector<double> rightAngle;

        leftAngle.assign(absAngle.begin(),absAngle.begin()+3);
        rightAngle.assign(absAngle.begin()+3,absAngle.begin()+6);

        pointData leftEnd=ForwardKinematic(leftAngle);
        pointData rightEnd=ForwardKinematic(rightAngle);

        emit recEndPos(leftEnd,true);//更新末端坐标
        emit recEndPos(rightEnd,false);

        //角度更新--暂调试使用
        emit recAbsAngle(absAngle);

        if(NumCanReceive<=0)
        {
//            Sleep(30);
            //            qDebug()<<"receive error";
            //            QString log;
            //            log.sprintf("%p",QThread::currentThread());
            //            qDebug()<<"test"<<++i<<log;
        }
        else
        {
            for(int ind=0;ind<NumCanReceive;++ind)
            {
                ReceiveId=pCanObj[ind].ID;
                for(int i=0;i<8;++i)
                {
                    ReceiveData[i]=pCanObj[ind].Data[i];
                    str=QString::number(ReceiveData[i],16);
                    str=QString("%2").arg(ReceiveData[i],2,16,QLatin1Char('0'));
                    if(i<7)
                    {
                        strRecData=strRecData+str+" ";
                    }
                    else
                    {
                        strRecData+=str;
                        strRecData=strRecData.toUpper();
                    }
                }
                strRecData+='\n';
                strRecId=QString("%8").arg(ReceiveId,8,16,QLatin1Char('0')).toUpper();
                emit rec(strRecId,strRecData);



                if(0x41==ReceiveData[0] && 0x45 == ReceiveData[1] && 0x01==ReceiveData[2])
                {

                    recIndex=ReceiveId-0x281;
                    count++;
                    if(false==flagAbsOrInc)
                    {
                        absNum[recIndex]=(ReceiveData[7]<<24)+(ReceiveData[6]<<16)+(ReceiveData[5]<<8)+ReceiveData[4];
                        absAngle[recIndex]=(static_cast<double>(absNum[recIndex])/65536)*180;
                        emit recAbsAngle(absAngle);
                    }
                    else
                    {
                        incNum[recIndex]=(ReceiveData[7]<<24)+(ReceiveData[6]<<16)+(ReceiveData[5]<<8)+ReceiveData[4];
                        //                    incAngle[recIndex]=static_cast<double>(incNum[recIndex])/65536*180;
                        //emit recIncNum(incNum);  增量式角度暂不启用
                    }
                    if(count>6&&false==flagDataRigth)//已完成一轮角度查询
                    {
                        flagDataRigth=true;
                        emit initChart();
                    }

                    vector<double> leftAngle;
                    vector<double> rightAngle;

                    for(size_t i=0;i<3;++i)
                    {
                        leftAngle.push_back(absNum[i]);
                        rightAngle.push_back(absNum[i+3]);

                    }

                    pointData leftEnd=ForwardKinematic(leftAngle);
                    pointData rightEnd=ForwardKinematic(rightAngle);

                    emit recEndPos(leftEnd,true);//更新末端坐标
                    emit recEndPos(rightEnd,false);
                }
                //数据库插入
                if(flagDBOpen==false&&flagRecAndInq==1){
                    m_sqlite2->initDB();

                    flagDBOpen=true;
                }
                else
                {
                    QSqlite::robotData s;
                    m_sqlite2->ExecAddSql(s);
                }


            }
        }

    }
}

void Controller::btnMoterRunClick(bool isForward,UINT index,QString angle)
{
    if(true==isForward)
    {
        MoterRunFor(index,angle);
    }
    else
    {
        MoterRunRev(index,angle);
    }
}

void Controller::MoterRunFor(UINT index,QString strangle)
{
    int angle=strangle.toInt();

    if(angle>=180)   angle=180;//角度限位
    if(angle<=0)  angle=0;

    vector<BYTE> angleData(4,0);//发送的角度四位字节，从低位至高位
    //BYTE angleData[4];
    angle*=22445;//试验估算值，22445脉冲约等于1°

    angleData[0]= angle     & 0x000000FF;
    angleData[1]=(angle>>8) & 0x000000FF;
    angleData[2]=(angle>>16)& 0x000000FF;
    angleData[3]=(angle>>24)& 0x000000FF;


    switch(index)//发送角度指令
    {
    case 1:sendbuf->ID=0x301;
        break;
    case 2:sendbuf->ID=0x302;
        break;
    case 3:sendbuf->ID=0x303;
        break;
    case 4:sendbuf->ID=0x304;
        break;
    case 5:sendbuf->ID=0x305;
        break;
    case 6:sendbuf->ID=0x306;
        break;
    default:break;
    }
    sendbuf->Data[0]=0x50;
    sendbuf->Data[1]=0x41;
    sendbuf->Data[4]=angleData[0];
    sendbuf->Data[5]=angleData[1];
    sendbuf->Data[6]=angleData[2];
    sendbuf->Data[7]=angleData[3];
    CanSend();
    Sleep(10);


    switch(index)//运行角度指令
    {
    case 1:sendbuf->ID=0x301;
        break;
    case 2:sendbuf->ID=0x302;
        break;
    case 3:sendbuf->ID=0x303;
        break;
    case 4:sendbuf->ID=0x304;
        break;
    case 5:sendbuf->ID=0x305;
        break;
    case 6:sendbuf->ID=0x306;
        break;
    default:break;
    }
    sendbuf->Data[0]=0x42;
    sendbuf->Data[1]=0x47;
    CanSend();
    Sleep(10);
}


void Controller::MoterRunRev(UINT index,QString strangle)
{
    int angle=strangle.toInt();

    if(angle>=180)   angle=180;//角度限位
    if(angle<=0)  angle=0;

    BYTE angleData[4];//发送的角度四位字节，从低位至高位
    angle*=(-22445);//试验估算值，22445脉冲约等于1°

    angleData[0]= angle& 0x000000FF;
    angleData[1]=(angle >> 8) & 0x000000FF;
    angleData[2]=(angle>>16)&0x000000FF;
    angleData[3]=(angle>>24)&0x000000FF;


    switch(index)//发送角度指令
    {
    case 1:sendbuf->ID=0x301;
        break;
    case 2:sendbuf->ID=0x302;
        break;
    case 3:sendbuf->ID=0x303;
        break;
    case 4:sendbuf->ID=0x304;
        break;
    case 5:sendbuf->ID=0x305;
        break;
    case 6:sendbuf->ID=0x306;
        break;
    default:break;
    }
    sendbuf->Data[0]=0x50;
    sendbuf->Data[1]=0x41;
    sendbuf->Data[4]=angleData[0];
    sendbuf->Data[5]=angleData[1];
    sendbuf->Data[6]=angleData[2];
    sendbuf->Data[7]=angleData[3];
    CanSend();
    Sleep(10);


    switch(index)//运行角度指令
    {
    case 1:sendbuf->ID=0x301;
        break;
    case 2:sendbuf->ID=0x302;
        break;
    case 3:sendbuf->ID=0x303;
        break;
    case 4:sendbuf->ID=0x304;
        break;
    case 5:sendbuf->ID=0x305;
        break;
    case 6:sendbuf->ID=0x306;
        break;
    default:break;
    }
    sendbuf->Data[0]=0x42;
    sendbuf->Data[1]=0x47;
    CanSend();
    Sleep(10);
}

//#define Link1Length 120.0 论文中d2
//#define Link2Length 264.0  论文中a2
//#define Link3WLength 127.0  论文中a3
//#define Link3HLength 213.0   论文中d4

pointData Controller::ForwardKinematic(vector<double> angleData)
{
    vector<double> angleTheta(3,0);//将角度值转为弧度值进行计算
    pointData out;
    for(size_t i=0;i<3;++i)
    {
    angleTheta[i]=angleData[i]*PI/180.0;
    }
    out.cal_x=Link3WLength*cos(angleTheta[0])*cos(angleTheta[1]+angleTheta[2])
            -Link3HLength*cos(angleTheta[0])*sin(angleTheta[1]+angleTheta[2])
            +Link2Length*cos(angleTheta[0])*cos(angleTheta[1])
            +Link1Length*sin(angleTheta[0]);
    out.cal_y=Link3WLength*sin(angleTheta[0])*cos(angleTheta[1]+angleTheta[2])
            -Link3HLength*sin(angleTheta[0])*sin(angleTheta[1]+angleTheta[2])
            +Link2Length*sin(angleTheta[0])*cos(angleTheta[1])
            -Link1Length*cos(angleTheta[0]);
    out.cal_z=Link3WLength*sin(angleTheta[1]+angleTheta[2])
            +Link3HLength*cos(angleTheta[1]+angleTheta[2])
            +Link2Length*sin(angleTheta[1]);
    return out;
}



void Controller::InverseKinematic(pointData point,bool isLeft)
{
    vector<double> now(3,0);
    if(isLeft)
    {
        now={absAngle[0],absAngle[1],absAngle[2]};
    }
    else
    {
        now={absAngle[3],absAngle[4],absAngle[5]};
    }

    vector<vector<double>> out;
    //反解计算有一定问题
    //#define Link1Length 120.0 论文中d2
    //#define Link2Length 264.0  论文中a2
    //#define Link3WLength 127.0  论文中a3
    //#define Link3HLength 213.0   论文中d4

//    θ = ATan(y / x)求出的θ取值范围是[-PI/2, PI/2]
//    θ = ATan2(y, x)求出的θ取值范围是[-PI, PI]

    double theta1_1=atan((sqrt(pow(point.pos_x,2)+pow(point.pos_y,2)-Link1Length*Link1Length))/Link1Length)
                   -atan(point.pos_x/point.pos_y);

    double theta1_2=atan((-sqrt(pow(point.pos_x,2)+pow(point.pos_y,2)-Link1Length*Link1Length))/Link1Length)
                   -atan(point.pos_x/point.pos_y);

    double k=(pow(point.pos_x,2)+pow(point.pos_y,2)+pow(point.pos_z,2)-145594.0)/528.0;

    double theta3_1=atan(Link3WLength/Link3HLength)
                   -atan(k/sqrt(61498-pow(k,2)));

    double theta3_2=atan(Link3WLength/Link3HLength)
                   -atan(k/-sqrt(61498-pow(k,2)));

    double theta2_1=atan2(((Link2Length*sin(theta3_1)-Link3HLength)*(point.pos_x*cos(theta1_1)
                            +point.pos_y*sin(theta1_1))+point.pos_z*(Link3WLength+Link2Length*cos(theta3_1))),
                        ((Link3WLength+Link2Length*cos(theta3_1))*(point.pos_x*cos(theta1_1)+point.pos_y*sin(theta1_1))
                            -point.pos_z*(Link2Length*sin(theta3_1)-Link3HLength)))
                        -theta3_1;//theta1_1 +theta3_1   test ok


    double theta2_2=atan(((Link2Length*sin(theta3_2)-Link3HLength)*(point.pos_x*cos(theta1_1)
                            +point.pos_y*sin(theta1_1))+point.pos_z*(Link3WLength+Link2Length*cos(theta3_2)))/
                        ((Link3WLength+Link2Length*cos(theta3_2))*(point.pos_x*cos(theta1_1)+point.pos_y*sin(theta1_1))
                            -point.pos_z*(Link2Length*sin(theta3_2)-Link3HLength)))
                        -theta3_2;//theta1_1 +theta3_2

    double theta2_3=atan(((Link2Length*sin(theta3_1)-Link3HLength)*(point.pos_x*cos(theta1_2)
                            +point.pos_y*sin(theta1_2))+point.pos_z*(Link3WLength+Link2Length*cos(theta3_1)))/
                       ((Link3WLength+Link2Length*cos(theta3_1))*(point.pos_x*cos(theta1_2)+point.pos_y*sin(theta1_2))
                            -point.pos_z*(Link2Length*sin(theta3_1)-Link3HLength)))
                       -theta3_1;//theta1_2 +theta3_1  test ok

    double theta2_4=atan(((Link2Length*sin(theta3_2)-Link3HLength)*(point.pos_x*cos(theta1_2)
                            +point.pos_y*sin(theta1_2))+point.pos_z*(Link3WLength+Link2Length*cos(theta3_2)))/
                       ((Link3WLength+Link2Length*cos(theta3_2))*(point.pos_x*cos(theta1_2)+point.pos_y*sin(theta1_2))
                            -point.pos_z*(Link2Length*sin(theta3_2)-Link3HLength)))
                       -theta3_2;//theta1_2 +theta3_2

    double angle1_1=theta1_1*180.0/PI;
    double angle1_2=theta1_2*180.0/PI;

    double angle3_1=theta3_1*180.0/PI;
    double angle3_2=theta3_2*180.0/PI;

    double angle2_1=theta2_1*180.0/PI;
    double angle2_2=theta2_2*180.0/PI;
    double angle2_3=theta2_3*180.0/PI;
    double angle2_4=theta2_4*180.0/PI;

    out.push_back({angle1_1,angle2_1,angle3_1});
    out.push_back({angle1_1,angle2_2,angle3_2});
    out.push_back({angle1_2,angle2_3,angle3_1});
    out.push_back({angle1_2,angle2_4,angle3_2});

    double min=DBL_MAX;
    double result;
    UINT index=0;
    for(UINT i=0;i<4;++i)
    {
        result=(out[i][0]-now[0])*ArmWeight1+(out[i][1]-now[1])*ArmWeight2+(out[i][2]-now[2])*ArmWeight3;
        if(result<min)
        {
            min=result;
            index=i;
        }
        else continue;
    }

    if(isLeft)
    {
        emit recInverseCal(out[index],true);
    }
    else
    {
        emit recInverseCal(out[index],false);
    }



//    if(isLeft)
//    {
//        btnMoterRunClick(1,out[index][0]);
//        btnMoterRunClick(2,out[index][1]);
//        btnMoterRunClick(3,out[index][2]);
//    }
//    else {
//        btnMoterRunClick(4,out[index][0]);
//        btnMoterRunClick(5,out[index][1]);
//        btnMoterRunClick(6,out[index][2]);
//    }
}

void Controller::btnMoterRunClick(UINT index,double angle)
{

    QString temp=QString::number(angle,10,4);
    btnMoterRunClick(true,index,temp);
}

void Controller::btnMoterStopClick(UINT index)
{
    switch(index)//运行角度指令
    {
    case 1:sendbuf->ID=0x301;
        break;
    case 2:sendbuf->ID=0x302;
        break;
    case 3:sendbuf->ID=0x303;
        break;
    case 4:sendbuf->ID=0x304;
        break;
    case 5:sendbuf->ID=0x305;
        break;
    case 6:sendbuf->ID=0x306;
        break;
    default:break;
    }
    sendbuf->Data[0]=0x53;
    sendbuf->Data[1]=0x54;
    CanSend();
    Sleep(10);
}

void Controller::btnSetMoterSpeedClick(UINT index,int speed)
{
    if(speed>1000||speed<-1000)//理论速度可达2500pulse/s
    {
        qDebug()<<"Speed too fast";
        return;
    }
    switch(index)//运行角度指令
    {
    case 1:sendbuf->ID=0x301;
        break;
    case 2:sendbuf->ID=0x302;
        break;
    case 3:sendbuf->ID=0x303;
        break;
    case 4:sendbuf->ID=0x304;
        break;
    case 5:sendbuf->ID=0x305;
        break;
    case 6:sendbuf->ID=0x306;
        break;
    default:break;
    }
    sendbuf->Data[0]=0x53;
    sendbuf->Data[1]=0x50;

    vector<BYTE> speedData(4,0);//发送的速度四位字节，从低位至高位

    speedData[0]= speed     & 0x000000FF;
    speedData[1]=(speed>>8) & 0x000000FF;
    speedData[2]=(speed>>16)& 0x000000FF;
    speedData[3]=(speed>>24)& 0x000000FF;
    sendbuf->Data[4]=speedData[0];
    sendbuf->Data[5]=speedData[1];
    sendbuf->Data[6]=speedData[2];
    sendbuf->Data[7]=speedData[3];
    CanSend();
    Sleep(10);
}
