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

    connect(this,&View::open,m_controller,&Controller::btnOpenClick);
    connect(this,&View::close,m_controller,&Controller::btnCloseClick);
    connect(this,&View::send,m_controller,&Controller::btnSendClick);
    connect(this,&View::enable,m_controller,&Controller::btnEnableClick);

    connect(m_receiver,&Controller::rec,this,&View::updateTest);
    connect(m_receiver,&Controller::recAbsAngle,this,&View::updateAbsAngle);
    connect(m_receiver,&Controller::recIncNum,this,&View::updateIncNum);


    //绘图使用
    QTimer *timer=new QTimer(this);
    timer->start(30);
    connect(timer,&QTimer::timeout,this,&View::getNow);
//    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
//    dateTicker->setDateTimeFormat("hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
//    ui->wgtMoter1->xAxis->setTicker(dateTicker);//设置X轴为时间轴
//    ui->wgtMoter1->xAxis->setLabel("Time/s");
//    ui->wgtMoter1->yAxis->setLabel("Angle/°");

    ui->wgtMoter1->xAxis->setTickLabels(true);//显示刻度标签

    ui->wgtMoter1->addGraph(ui->wgtMoter1->xAxis, ui->wgtMoter1->yAxis);

    ui->wgtMoter1->setInteractions(QCP::iRangeDrag //可平移
                                | QCP::iSelectPlottables//使所有图例可见
                                | QCP::iRangeZoom); //可滚轮缩放
//                              | QCP::iSelectLegend );//可选中图例

    ui->wgtMoter1->yAxis->setRange(-180, 180);//设置y轴范围为-180至180
    refreshTimer = startTimer(30, Qt::CoarseTimer);//刷新计数器
    sampleTimer = startTimer(30, Qt::CoarseTimer);//采样计数器
    lastPoint.setX(timecount);
    lastPoint.setY(absAngle[0]);
}

View::~View()
{
    flagRecAndInq=2;
    //    receiveThread->quit();
    //    receiveThread->wait();
    delete ui;
}

//-----------------------以下为图表绘图部分-------------------------//
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
    }

    if(event->timerId() == sampleTimer)//30ms-数据采样时间
    {
        newPoint.setX(timecount);
        newPoint.setY(timecount*timecount);
        qDebug() << newPoint.x() <<  newPoint.y();
        /*在新的点和上一个采样点之间，线性插值100个点*/
//        int n = 100;
//        double dx = (newPoint.x() - lastPoint.x()) / 100.0;//线性插值
//        double dy = (newPoint.y() - lastPoint.y()) / 100.0;//线性插值
//        for(int i = 1; i <= n; i++)
//        {
//            ui->wgtMoter1->graph(0)->addData(lastPoint.x() + dx * i, lastPoint.y() + dy * i);
//        }
        ui->wgtMoter1->graph(0)->addData(lastPoint.x(),lastPoint.y());
        ui->wgtMoter1->graph(0)->rescaleKeyAxis(true);//根据x轴最高点自动缩放坐标轴
        lastPoint.setX(newPoint.x());
        lastPoint.setY(newPoint.y());
    }
}
//-----------------------图表绘图部分结束-------------------------//

void View::on_btnOpen_clicked()
{
    emit open();

    //    //------inquireThread、receiveThread在点open按钮时初始化------------//
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

void View::on_btnClose_clicked()
{
    emit close();
    flagRecAndInq=2;
}

void View::on_btnSend_clicked()
{
    QString qstr_id=ui->edtId->text();
    QString qstr_data=ui->edtData->text();
    emit send(qstr_id, qstr_data);
}

void View::on_BtnEnable_clicked()
{
    emit enable();
}

void View::updateTest(QString receiveId,QString receiveData)
{

    ui->edttest1->setText(receiveId);
    ui->edttest2->setText(receiveData);
}

void View::updateAbsAngle(vector<double> absAngle)
{
    ui->edtMoter1Angle->setText(QString::number(absAngle[0],10,3));
    ui->edtMoter2Angle->setText(QString::number(absAngle[1],10,3));
    ui->edtMoter3Angle->setText(QString::number(absAngle[2],10,3));
    ui->edtMoter4Angle->setText(QString::number(absAngle[3],10,3));
    ui->edtMoter5Angle->setText(QString::number(absAngle[4],10,3));
    ui->edtMoter6Angle->setText(QString::number(absAngle[5],10,3));
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
