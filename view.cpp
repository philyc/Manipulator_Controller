#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);

    m_controller=new Controller();

    connect(this,&View::open,m_controller,&Controller::btnOpenClick);
    connect(this,&View::close,m_controller,&Controller::btnCloseClick);
    connect(this,&View::send,m_controller,&Controller::btnSendClick);
    connect(this,&View::enable,m_controller,&Controller::btnEnableClick);

    //        receiveThread=new QThread;
    //    m_controller->moveToThread(receiveThread);
    //    connect(receiveThread,SIGNAL(started()),m_controller,SLOT(receive()));
    //    connect(receiveThread,SIGNAL(finished()),receiveThread,SLOT(deleteLater()));
    connect(m_controller,&Controller::rec,this,&View::updateWindows);
    //    receiveThread->start();
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

    //------receiveThread在点open按钮时初始化------------//
    receiveThread=new QThread;
    if(flagReceive==0)
    {
        m_controller->moveToThread(receiveThread);//只有第一次需要进行movetothread;
    }
    connect(receiveThread,SIGNAL(started()),m_controller,SLOT(receive()));
    connect(receiveThread,SIGNAL(finished()),receiveThread,SLOT(deleteLater()));
    receiveThread->start();
    flagReceive=1;
    //-------无论如何关闭，receive函数均在子线程下运行--------------//
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

void View::updateWindows(QString receiveId,QString receiveData)
{

}
