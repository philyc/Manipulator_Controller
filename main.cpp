#include "view.h"
#include "controller.h"
#include "model.h"
#include "qmysql.h"



#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<vector<double>>("vector<double>");//注册类型
    qRegisterMetaType<vector<long>>("vector<long>");




    View w;
    w.show();

    return a.exec();
}
