#include "view.h"
#include "ui_view.h"


View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

    //    QString log;
    //    log.sprintf("%p",QThread::currentThread());
    //    qDebug()<<"Main test"<<log;

    m_controller=new Controller();
    m_receiver=new Controller();//receive线程对应的QObject
    m_inquirer=new Controller();//inquire线程对应的QObject

    m_sqlite=new QSqlite();

    connect(this,&View::open,m_controller,&Controller::btnOpenClick);
    connect(this,&View::close,m_controller,&Controller::btnCloseClick);
    connect(this,&View::send,m_controller,&Controller::btnSendClick);
    connect(this,&View::enable,m_controller,&Controller::btnEnableClick);
    connect(this,&View::moterRun,m_controller,static_cast<void (Controller::*)(bool,UINT,QString)>(&Controller::btnMoterRunClick));
    connect(this,&View::moterStop,m_controller,&Controller::btnMoterStopClick);
    connect(this,&View::inverseCal,m_controller,&Controller::InverseKinematic);


    //图表初始化
    connect(this,&View::open,this,&View::initChart);//开始时初始化图表

    //数据库相关
    connect(this,&View::closeDB,m_sqlite,&QSqlite::closeDB);

    //消息更新
    connect(m_receiver,&Controller::rec,this,&View::updateTest);
    connect(m_receiver,&Controller::recAbsAngle,this,&View::updateAbsAngle);
    connect(m_receiver,&Controller::recIncNum,this,&View::updateIncNum);
    connect(m_receiver,&Controller::recEndPos,this,&View::updateEndPos);
    connect(m_controller,&Controller::recInverseCal,this,&View::updateiInverseCal);

    //opengl窗口
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->addWidget(openGLWidget);
    ui->openGLWidget->setFocusPolicy(Qt::StrongFocus);
    ui->openGLWidget->setLayout(centralLayout);
    connect(this,&View::keyPressEvent,openGLWidget,&OpenGLWidget::keyPressEvent);
    connect(this,&View::wheelEvent,openGLWidget,&OpenGLWidget::wheelEvent);


    ui->doubleSpinBox->setRange(-90.0,90.0);
    ui->doubleSpinBox->setSingleStep(1);
    ui->doubleSpinBox->setValue(absAngle[0]);
    ui->doubleSpinBox_2->setRange(-90.0,90.0);
    ui->doubleSpinBox_2->setSingleStep(1);
    ui->doubleSpinBox_2->setValue(absAngle[1]);
    ui->doubleSpinBox_3->setRange(-90.0,90.0);
    ui->doubleSpinBox_3->setSingleStep(1);
    ui->doubleSpinBox_3->setValue(absAngle[2]);

    ui->doubleSpinBox_4->setRange(-90.0,90.0);
    ui->doubleSpinBox_4->setSingleStep(1);
    ui->doubleSpinBox_4->setValue(absAngle[3]);
    ui->doubleSpinBox_5->setRange(-90.0,90.0);
    ui->doubleSpinBox_5->setSingleStep(1);
    ui->doubleSpinBox_5->setValue(absAngle[4]);
    ui->doubleSpinBox_6->setRange(-90.0,90.0);
    ui->doubleSpinBox_6->setSingleStep(1);
    ui->doubleSpinBox_6->setValue(absAngle[5]);
}

View::~View()
{
    flagRecAndInq=2;
    //    receiveThread->quit();
    //    receiveThread->wait();
    delete ui;
}

//**以下为绘图部分**//
void View::initChart()
{
    //绘图使用
    if(flagIsOpen){
        QTimer *timer=new QTimer(this);
        timer->start(30);
        connect(timer,&QTimer::timeout,this,&View::getNow);
        //    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        //    dateTicker->setDateTimeFormat("hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        //    ui->wgtMoter1->xAxis->setTicker(dateTicker);//设置X轴为时间轴
        //    ui->wgtMoter1->xAxis->setLabel("Time/s");
        //    ui->wgtMoter1->yAxis->setLabel("Angle/°");
        refreshTimer = startTimer(30, Qt::CoarseTimer);//刷新计数器
        sampleTimer = startTimer(30, Qt::CoarseTimer);//采样计数器
        for(UINT i=0;i<6;++i)
        {
            lastPoint[i].setX(timecount);
            lastPoint[i].setY(absAngle[i]);
        }

        ui->wgtMoter1->xAxis->setTickLabels(true);//显示刻度标签
        ui->wgtMoter1->addGraph(ui->wgtMoter1->xAxis, ui->wgtMoter1->yAxis);
        ui->wgtMoter1->setInteractions(QCP::iRangeDrag //可平移
                                       | QCP::iSelectPlottables//使所有图例可见
                                       | QCP::iRangeZoom); //可滚轮缩放
        //                              | QCP::iSelectLegend );//可选中图例
        ui->wgtMoter1->yAxis->setRange(-30, 30);//设置y轴范围为-30至30




        ui->wgtMoter2->xAxis->setTickLabels(true);//显示刻度标签
        ui->wgtMoter2->addGraph(ui->wgtMoter2->xAxis, ui->wgtMoter2->yAxis);
        ui->wgtMoter2->setInteractions(QCP::iRangeDrag //可平移
                                       | QCP::iSelectPlottables//使所有图例可见
                                       | QCP::iRangeZoom); //可滚轮缩放
        //                              | QCP::iSelectLegend );//可选中图例
        ui->wgtMoter2->yAxis->setRange(-30, 30);//设置y轴范围为-30至30




        ui->wgtMoter3->xAxis->setTickLabels(true);//显示刻度标签
        ui->wgtMoter3->addGraph(ui->wgtMoter3->xAxis, ui->wgtMoter3->yAxis);
        ui->wgtMoter3->setInteractions(QCP::iRangeDrag //可平移
                                       | QCP::iSelectPlottables//使所有图例可见
                                       | QCP::iRangeZoom); //可滚轮缩放
        //                              | QCP::iSelectLegend );//可选中图例

        ui->wgtMoter3->yAxis->setRange(-30, 30);//设置y轴范围为-30至30




        ui->wgtMoter4->xAxis->setTickLabels(true);//显示刻度标签
        ui->wgtMoter4->addGraph(ui->wgtMoter4->xAxis, ui->wgtMoter4->yAxis);
        ui->wgtMoter4->setInteractions(QCP::iRangeDrag //可平移
                                       | QCP::iSelectPlottables//使所有图例可见
                                       | QCP::iRangeZoom); //可滚轮缩放
        //                              | QCP::iSelectLegend );//可选中图例
        ui->wgtMoter4->yAxis->setRange(-30, 30);//设置y轴范围为-30至30





        ui->wgtMoter5->xAxis->setTickLabels(true);//显示刻度标签
        ui->wgtMoter5->addGraph(ui->wgtMoter5->xAxis, ui->wgtMoter5->yAxis);
        ui->wgtMoter5->setInteractions(QCP::iRangeDrag //可平移
                                       | QCP::iSelectPlottables//使所有图例可见
                                       | QCP::iRangeZoom); //可滚轮缩放
        //                              | QCP::iSelectLegend );//可选中图例
        ui->wgtMoter5->yAxis->setRange(-30, 30);//设置y轴范围为-30至30




        ui->wgtMoter6->xAxis->setTickLabels(true);//显示刻度标签
        ui->wgtMoter6->addGraph(ui->wgtMoter6->xAxis, ui->wgtMoter6->yAxis);
        ui->wgtMoter6->setInteractions(QCP::iRangeDrag //可平移
                                       | QCP::iSelectPlottables//使所有图例可见
                                       | QCP::iRangeZoom); //可滚轮缩放
        //                              | QCP::iSelectLegend );//可选中图例
        ui->wgtMoter6->yAxis->setRange(-30, 30);//设置y轴范围为-30至30
    }
}

void View::getNow()
{
    timecount+=0.03;
    //    return static_cast<double>(QDateTime::currentMSecsSinceEpoch()) / 1000.0;
}

void View::timerEvent(QTimerEvent *event)
{

    if(event->timerId() == refreshTimer)//30ms-图表刷新时间
    {
        ui->wgtMoter1->replot();
        ui->wgtMoter2->replot();
        ui->wgtMoter3->replot();
        ui->wgtMoter4->replot();
        ui->wgtMoter5->replot();
        ui->wgtMoter6->replot();
    }

    if(event->timerId() == sampleTimer)//30ms-数据采样时间
    {
        for(UINT i=0;i<6;++i)
        {
            newPoint[i].setX(timecount);
            newPoint[i].setY(absAngle[i]);
            //            qDebug() << newPoint[i].x() <<  newPoint[i].y();
        }

        /*在新的点和上一个采样点之间，线性插值100个点*/
        //        int n = 100;
        //        double dx = (newPoint.x() - lastPoint.x()) / 100.0;//线性插值
        //        double dy = (newPoint.y() - lastPoint.y()) / 100.0;//线性插值
        //        for(int i = 1; i <= n; i++)
        //        {
        //            ui->wgtMoter1->graph(0)->addData(lastPoint.x() + dx * i, lastPoint.y() + dy * i);
        //        }
        ui->wgtMoter1->graph(0)->addData(lastPoint[0].x(),lastPoint[0].y());
        ui->wgtMoter2->graph(0)->addData(lastPoint[1].x(),lastPoint[1].y());
        ui->wgtMoter3->graph(0)->addData(lastPoint[2].x(),lastPoint[2].y());
        ui->wgtMoter4->graph(0)->addData(lastPoint[3].x(),lastPoint[3].y());
        ui->wgtMoter5->graph(0)->addData(lastPoint[4].x(),lastPoint[4].y());
        ui->wgtMoter6->graph(0)->addData(lastPoint[5].x(),lastPoint[5].y());

        //        ui->wgtMoter1->graph(0)->rescaleKeyAxis(true);//根据x轴最高点自动缩放坐标轴
        //        ui->wgtMoter1->graph(0)->rescaleValueAxis(true);//根据y轴最高点自动缩放坐标轴
        ui->wgtMoter1->graph(0)->rescaleAxes(true);
        ui->wgtMoter2->graph(0)->rescaleAxes(true);
        ui->wgtMoter3->graph(0)->rescaleAxes(true);
        ui->wgtMoter4->graph(0)->rescaleAxes(true);
        ui->wgtMoter5->graph(0)->rescaleAxes(true);
        ui->wgtMoter6->graph(0)->rescaleAxes(true);

        for(UINT i=0;i<6;++i)
        {
            lastPoint[i].setX(newPoint[i].x());
            lastPoint[i].setY(newPoint[i].y());
        }
    }
}
//**图表绘图部分结束**//



void View::on_btnOpen_clicked()
{
    emit open();

    //    //------inquireThread、receiveThread在点open按钮时初始化------------//
    if(flagIsOpen){
        inquireThread=new QThread;
        receiveThread=new QThread;
        if(flagRecAndInq==0)
        {
            m_inquirer->moveToThread(inquireThread);//只有第一次需要进行movetothread;
            m_receiver->moveToThread(receiveThread);//只有第一次需要进行movetothread;
        }
        connect(inquireThread,&QThread::started,m_inquirer,&Controller::inquire);
        connect(inquireThread,&QThread::finished,inquireThread,&QThread::deleteLater);
        connect(receiveThread,&QThread::started,m_receiver,&Controller::receive);
        connect(receiveThread,&QThread::finished,receiveThread,&QThread::deleteLater);
        inquireThread->start();
        receiveThread->start();
        flagRecAndInq=1;
    }
    else return;
}

void View::on_btnClose_clicked()
{
    emit close();
    emit closeDB(m_sqlite->db);
    flagRecAndInq=2;
    flagDBOpen=false;
}

void View::on_btnSend_clicked()
{
    QString qstr_id=ui->edtId->text();
    QString qstr_data=ui->edtSendData->text();
    emit send(qstr_id, qstr_data);
}

void View::on_BtnEnable_clicked()
{
    emit enable();
}

void View::updateTest(QString receiveId,QString receiveData)
{

    ui->edtRecieveId->setText(receiveId);
    ui->edtRecieveData->setText(receiveData);
}

void View::updateAbsAngle(vector<double> absAngle)
{
    ui->edtMoter1AbsAngle->setText(QString::number(absAngle[0],10,3));
    ui->edtMoter2AbsAngle->setText(QString::number(absAngle[1],10,3));
    ui->edtMoter3AbsAngle->setText(QString::number(absAngle[2],10,3));
    ui->edtMoter4AbsAngle->setText(QString::number(absAngle[3],10,3));
    ui->edtMoter5AbsAngle->setText(QString::number(absAngle[4],10,3));
    ui->edtMoter6AbsAngle->setText(QString::number(absAngle[5],10,3));
}

void View::updateIncNum(vector<long> incNum)
{
    ui->edtMoter1AddAngle->setText(QString::number(incNum[0],10));
    ui->edtMoter2AddAngle->setText(QString::number(incNum[1],10));
    ui->edtMoter3AddAngle->setText(QString::number(incNum[2],10));
    ui->edtMoter4AddAngle->setText(QString::number(incNum[3],10));
    ui->edtMoter5AddAngle->setText(QString::number(incNum[4],10));
    ui->edtMoter6AddAngle->setText(QString::number(incNum[5],10));
}

void View::updateEndPos(pointData point,bool isLeft)
{
    if(isLeft)
    {
        ui->edtLeftEndPosX->setText(QString::number(point.cal_x,10,3));
        ui->edtLeftEndPosY->setText(QString::number(point.cal_y,10,3));
        ui->edtLeftEndPosZ->setText(QString::number(point.cal_z,10,3));
    }
    else
    {
        ui->edtRightEndPosX->setText(QString::number(point.cal_x,10,3));
        ui->edtRightEndPosY->setText(QString::number(point.cal_y,10,3));
        ui->edtRightEndPosZ->setText(QString::number(point.cal_z,10,3));
    }
}

void View::on_btnMoter1RunFor_clicked()
{
    QString temp=ui->edtMoter1RunAngle->text();
    emit moterRun(true,1,temp);
}

void View::on_btnMoter1RunRev_clicked()
{
    QString temp=ui->edtMoter1RunAngle->text();
    emit moterRun(false,1,temp);
}

void View::on_btnMoter2RunFor_clicked()
{
    QString temp=ui->edtMoter2RunAngle->text();
    emit moterRun(true,2,temp);
}

void View::on_btnMoter2RunRev_clicked()
{
    QString temp=ui->edtMoter2RunAngle->text();
    emit moterRun(false,2,temp);
}

void View::on_btnMoter3RunFor_clicked()
{
    QString temp=ui->edtMoter3RunAngle->text();
    emit moterRun(true,3,temp);
}

void View::on_btnMoter3RunRev_clicked()
{
    QString temp=ui->edtMoter3RunAngle->text();
    emit moterRun(false,3,temp);
}

void View::on_btnMoter4RunFor_clicked()
{
    QString temp=ui->edtMoter4RunAngle->text();
    emit moterRun(true,4,temp);
}

void View::on_btnMoter4RunRev_clicked()
{
    QString temp=ui->edtMoter4RunAngle->text();
    emit moterRun(false,4,temp);
}

void View::on_btnMoter5RunFor_clicked()
{
    QString temp=ui->edtMoter5RunAngle->text();
    emit moterRun(true,5,temp);
}

void View::on_btnMoter5RunRev_clicked()
{
    QString temp=ui->edtMoter5RunAngle->text();
    emit moterRun(false,5,temp);
}

void View::on_btnMoter6RunFor_clicked()
{
    QString temp=ui->edtMoter6RunAngle->text();
    emit moterRun(true,6,temp);
}

void View::on_btnMoter6RunRev_clicked()
{
    QString temp=ui->edtMoter6RunAngle->text();
    emit moterRun(false,6,temp);
}


void View::on_btnMoter1RunStop_clicked()
{
    emit moterStop(1);
}

void View::on_btnMoter2RunStop_clicked()
{
    emit moterStop(2);
}

void View::on_btnMoter3RunStop_clicked()
{
    emit moterStop(3);
}

void View::on_btnMoter4RunStop_clicked()
{
    emit moterStop(4);
}

void View::on_btnMoter5RunStop_clicked()
{
    emit moterStop(5);
}

void View::on_btnMoter6RunStop_clicked()
{
    emit moterStop(6);
}

//void View::on_btnMoter1RunStopAll_clicked()
//{
//for(UINT i=1;i<7;++i)
//{
//    emit moterStop(i);
//}

//}

void View::on_btnShoulderCooRunFor_clicked()
{
    QString temp=ui->edtShoulderCooRunAngle->text();
    emit moterRun(true,1,temp);
    emit moterRun(false,4,temp);//对称放置时以1号电机方向为准，4号电机需反向
}

void View::on_btnShoulderCooRunRev_clicked()
{
    QString temp=ui->edtShoulderCooRunAngle->text();
    emit moterRun(false,1,temp);
    emit moterRun(true,4,temp);//对称放置时以1号电机方向为准，4号电机需反向
}

void View::on_btnShoulderCooRunStop_clicked()
{
    emit moterStop(1);
    emit moterStop(4);
}

void View::on_btnArm1CooRunFor_clicked()
{
    QString temp=ui->edtShoulderCooRunAngle->text();
    emit moterRun(true,2,temp);
    emit moterRun(false,5,temp);//对称放置时以2号电机方向为准，5号电机需反向
}

void View::on_btnArm1CooRunRev_clicked()
{
    QString temp=ui->edtShoulderCooRunAngle->text();
    emit moterRun(false,2,temp);
    emit moterRun(true,5,temp);//对称放置时以2号电机方向为准，5号电机需反向
}

void View::on_btnArm1CooRunStop_clicked()
{
    emit moterStop(2);
    emit moterStop(5);
}

void View::on_btnArm2CooRunFor_clicked()
{
    QString temp=ui->edtShoulderCooRunAngle->text();
    emit moterRun(true,3,temp);
    emit moterRun(false,6,temp);//对称放置时以3号电机方向为准，6号电机需反向
}

void View::on_btnArm2CooRunRev_clicked()
{
    QString temp=ui->edtShoulderCooRunAngle->text();
    emit moterRun(false,3,temp);
    emit moterRun(true,6,temp);//对称放置时以3号电机方向为准，6号电机需反向
}

void View::on_btnArm2CooRunStop_clicked()
{
    emit moterStop(3);
    emit moterStop(6);
}

void View::on_btnMoterRunStopAll_clicked()
{
    for(UINT i=1;i<7;++i)
    {
        emit moterStop(i);
    }
}

void View::on_btnCalcLeftRev_clicked()
{
    QString temp_X=ui->edtLeftSetX->text();
    QString temp_Y=ui->edtLeftSetY->text();
    QString temp_Z=ui->edtLeftSetZ->text();
    pointData aim;
    aim.pos_x=temp_X.toDouble();
    aim.pos_y=temp_Y.toDouble();
    aim.pos_z=temp_Z.toDouble();
    emit inverseCal(aim,true);
}



void View::on_btnCalcRightRev_clicked()
{
    QString temp_X=ui->edtRightSetX->text();
    QString temp_Y=ui->edtRightSetY->text();
    QString temp_Z=ui->edtRightSetZ->text();
    pointData aim;
    aim.pos_x=temp_X.toDouble();
    aim.pos_y=temp_Y.toDouble();
    aim.pos_z=temp_Z.toDouble();
    emit inverseCal(aim,false);
}

void View::updateiInverseCal(vector<double> calAngel,bool isLeft)
{
    if(isLeft)
    {
        ui->edtLeftCalcJoint1Angle->setText(QString::number(calAngel[0],10,3));
        ui->edtLeftCalcJoint2Angle->setText(QString::number(calAngel[1],10,3));
        ui->edtLeftCalcJoint3Angle->setText(QString::number(calAngel[2],10,3));
    }
    else
    {
        ui->edtRightCalcJoint1Angle->setText(QString::number(calAngel[0],10,3));
        ui->edtRightCalcJoint2Angle->setText(QString::number(calAngel[1],10,3));
        ui->edtRightCalcJoint3Angle->setText(QString::number(calAngel[2],10,3));
    }
}

void View::on_btnP2PLeftStop_clicked()
{
    emit moterStop(1);
    emit moterStop(2);
    emit moterStop(3);
}

void View::on_btnP2PRightStop_clicked()
{
    for(UINT i=4;i<7;++i)
    {
        emit moterStop(i);
    }
}

void View::on_btnP2PLeftMove_clicked()
{
    emit moterRun(true,1,ui->edtLeftCalcJoint1Angle->text());
    emit moterRun(true,2,ui->edtLeftCalcJoint2Angle->text());
    emit moterRun(true,3,ui->edtLeftCalcJoint3Angle->text());
}

void View::on_btnP2PRightMove_clicked()
{
    emit moterRun(true,4,ui->edtRightCalcJoint1Angle->text());
    emit moterRun(true,5,ui->edtRightCalcJoint2Angle->text());
    emit moterRun(true,6,ui->edtRightCalcJoint3Angle->text());
}

void View::on_doubleSpinBox_valueChanged(double arg1)
{
    absAngle[0]=arg1;
}

void View::on_doubleSpinBox_2_valueChanged(double arg1)
{
    absAngle[1]=arg1;
}

void View::on_doubleSpinBox_3_valueChanged(double arg1)
{
    absAngle[2]=arg1;
}


void View::on_doubleSpinBox_4_valueChanged(double arg1)
{
    absAngle[3]=arg1;
}

void View::on_doubleSpinBox_5_valueChanged(double arg1)
{
    absAngle[4]=arg1;
}

void View::on_doubleSpinBox_6_valueChanged(double arg1)
{
    absAngle[5]=arg1;
}
