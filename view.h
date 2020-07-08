#ifndef VIEW_H
#define VIEW_H
#pragma once

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QVBoxLayout>

#include "openglwidget.h"
#include "shader.h"
#include "controller.h"
#include "model.h"
#include "qcustomplot.h"
#include "qsqlite.h"




QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE



class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);

    void widgetshow(QCustomPlot *widget,int recIndex);

    ~View();

    OpenGLWidget* openGLWidget = new OpenGLWidget();

public:

    //线程使用
    Controller* m_receiver;//receive线程对应的QObject
    Controller* m_inquirer;//inquire线程对应的QObject
    Controller* m_controller;//其他引用函数
    QSqlite* m_sqlite;//sqlite相关
    Model* m_model;
    QThread *receiveThread;
    QThread *inquireThread;


    //绘图使用
    double timecount=0;//计时
    int refreshTimer;//刷新图像的定时器
    int sampleTimer;//模拟采样的定时器
    QPointF newPoint[6];
    QPointF lastPoint[6];//两点绘图，减少数据量
    void initChart();
    void getNow();//更新timecount,现为每30ms更新一次
    void timerEvent(QTimerEvent *event);//绘图主函数

    void closeEvent(QCloseEvent*event);

signals:

    void open();
    void close();
    void send(QString Id,QString Data);
    void enable();
    void moterRun(bool isForward,UINT index,QString angle);
    void moterStop(UINT index);

    void closeDB(QSqlDatabase db);
    void inverseCal(pointData aim,bool isLeft);
    void setspeed(UINT index,int speed);

signals:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);


public slots:


private slots:
    void on_btnOpen_clicked();

    void on_btnClose_clicked();

    void on_btnSend_clicked();

    void on_BtnEnable_clicked();

    void updateTest(QString receiveId,QString receiveData);//显示接收到的ID和Data

    void updateAbsAngle(vector<double> absAngle);//更新绝对值编码器反馈的角度

    void updateIncNum(vector<long> incNum);//更新增量式编码器反馈的数值

    void updateEndPos(pointData point,bool isLeft);

    void updateInverseCal(vector<double> calAngel,bool isLeft);

    void on_btnMoter1RunFor_clicked();

    void on_btnMoter1RunRev_clicked();

    void on_btnMoter2RunFor_clicked();

    void on_btnMoter2RunRev_clicked();

    void on_btnMoter3RunFor_clicked();

    void on_btnMoter3RunRev_clicked();

    void on_btnMoter4RunFor_clicked();

    void on_btnMoter4RunRev_clicked();

    void on_btnMoter5RunFor_clicked();

    void on_btnMoter5RunRev_clicked();

    void on_btnMoter6RunFor_clicked();

    void on_btnMoter6RunRev_clicked();


    void on_btnMoter1RunStop_clicked();

    void on_btnMoter2RunStop_clicked();

    void on_btnMoter3RunStop_clicked();

    void on_btnMoter4RunStop_clicked();

    void on_btnMoter5RunStop_clicked();

    void on_btnMoter6RunStop_clicked();

    void on_btnShoulderCooRunFor_clicked();

    void on_btnShoulderCooRunRev_clicked();

    void on_btnShoulderCooRunStop_clicked();

    void on_btnArm1CooRunFor_clicked();

    void on_btnArm1CooRunRev_clicked();

    void on_btnArm1CooRunStop_clicked();

    void on_btnArm2CooRunFor_clicked();

    void on_btnArm2CooRunRev_clicked();

    void on_btnArm2CooRunStop_clicked();

    void on_btnMoterRunStopAll_clicked();

    void on_btnCalcLeftRev_clicked();

    void on_btnCalcRightRev_clicked();

    void on_btnP2PLeftStop_clicked();

    void on_btnP2PRightStop_clicked();

    void on_btnP2PLeftMove_clicked();

    void on_btnP2PRightMove_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_6_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_btn3DTestState_clicked();

    void on_Btn3DWorkState_clicked();

    void on_btnMoter1SetSpeed_clicked();

    void on_btnMoter2SetSpeed_clicked();

    void on_btnMoter3SetSpeed_clicked();

    void on_btnMoter4SetSpeed_clicked();

    void on_btnMoter5SetSpeed_clicked();

    void on_btnMoter6SetSpeed_clicked();

    void on_edtRecieveData_textChanged();

    void on_BtnStopRec_clicked();

    void on_btnTest_clicked();

private:
    Ui::View *ui;

};
#endif // VIEW_H
