#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>

class Contorller : public QObject
{
    Q_OBJECT
public:
    explicit Contorller(){}

public:
    int flagReceive=0;//0为初始关闭，1为打开，2为关闭程序

signals:



public slots:
    void receive();//线程处理函数
};



#endif // MYTHREAD_H
