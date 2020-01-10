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

    QTimer *timer=new QTimer(this);
    timer->start(1000);

    connect(timer,&QTimer::timeout,this,&View::timeUpdate);

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
}

View::~View()
{
    flagRecAndInq=2;
    //    receiveThread->quit();
    //    receiveThread->wait();
    delete ui;
}



void View::widgetshow(QCustomPlot *widget,int recIndex)
{
    QVector<int> i;
    widget->addGraph();
    widget->graph(0)->setPen(QPen(Qt::red));
    widget->xAxis->setLabel("Time(s)");
    widget->yAxis->setLabel("Angle(°)");
}


void View::timeUpdate()
{
    QTime t;
    t=QTime::currentTime();
    widgetshow(ui->wgtMoter1,recIndex);

}


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
