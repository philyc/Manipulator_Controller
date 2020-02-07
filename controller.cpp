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
    //    View *m_view=new View();

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
    int NumCanSend=static_cast<int>(VCI_Transmit(devtype,devindex,static_cast<DWORD>(0),sendbuf,1));
    if(NumCanSend<1){
        switch (NumCanSend) {
        case -1:qDebug()<<"Device isn't open";return;
            //        case 0:qDebug()<<"send error";return;
        default:return;
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
            Sleep(10);
        }

        Sleep(10);
        flagAbsOrInc=true;
        for(UINT i=1;i<7;++i)
        {
            sendbuf->ID=0x300+i;
            sendbuf->Data[0]=0x50;
            sendbuf->Data[1]=0x58;
            CanSend();
            Sleep(10);
        }

        Sleep(50);
        qDebug()<<"Inquire rest";
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
    while(flagRecAndInq)
    {
        VCI_CAN_OBJ pCanObj[200];
        int NumCanReceive;
        QString strRecId,strRecData,str;
        NumCanReceive=static_cast<int>(VCI_Receive(devtype,devindex,0,pCanObj,200,0));
        robotData s;
        emit insertSql(s,sqlTableName);
        if(NumCanReceive<=0)
        {
            Sleep(30);
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
                strRecId=QString("%8").arg(ReceiveId,8,16,QLatin1Char('0')).toUpper();

                emit rec(strRecId,strRecData);
                recIndex=ReceiveId-0x281;
                if(false==flagAbsOrInc)
                {
                    absNum[recIndex]=(ReceiveData[7]<<24)+(ReceiveData[6]<<16)+(ReceiveData[5]<<8)+ReceiveData[4];
                    absAngle[recIndex]=static_cast<double>(absNum[recIndex])/65536*180;
                    emit recAbsAngle(absAngle);
                }
                else
                {
                    incNum[recIndex]=(ReceiveData[7]<<24)+(ReceiveData[6]<<16)+(ReceiveData[5]<<8)+ReceiveData[4];
                    //                    incAngle[recIndex]=static_cast<double>(incNum[recIndex])/65536*180;
                    emit recIncNum(incNum);
                }
//                robotData s;
//                emit insertSql(s,sqlTableName);
            }
        }
        Sleep(30);
        if(flagRecAndInq==2)
        {
            return;
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


