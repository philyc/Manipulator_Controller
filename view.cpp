#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

    QString log;
    log.sprintf("%p",QThread::currentThread());
    qDebug()<<"Main test"<<log;

    m_controller=new Controller();
    m_receiver=new Controller();//receive线程对应的QObject
    m_inquirer=new Controller();//inquire线程对应的QObject

    connect(this,&View::open,m_controller,&Controller::btnOpenClick);
    connect(this,&View::close,m_controller,&Controller::btnCloseClick);
    connect(this,&View::send,m_controller,&Controller::btnSendClick);
    connect(this,&View::enable,m_controller,&Controller::btnEnableClick);

    connect(m_receiver,&Controller::rec,this,&View::updateTest);
}

View::~View()
{
    flagReceive=2;
    //    receiveThread->quit();
    //    receiveThread->wait();
    delete ui;
}


void View::on_btnOpen_clicked()
{
    emit open();


    //    //------inquireThread、receiveThread在点open按钮时初始化------------//
    inquireThread=new QThread;
    receiveThread=new QThread;
    if(flagReceive==0)
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

    flagReceive=1;
}

void View::on_btnClose_clicked()
{
    emit close();
    flagReceive=2;
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
