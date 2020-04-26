#include "view.h"
#include "controller.h"
#include "model.h"
#include "qsqlite.h"


#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strPath ="F:/hust/underwater/Re/Manipulator/resource/img/Icon1.png";
    a.setWindowIcon(QIcon(strPath));
    qRegisterMetaType<vector<double>>("vector<double>");//注册类型
    qRegisterMetaType<vector<long>>("vector<long>");
    qRegisterMetaType<robotData>("robotData");
    qRegisterMetaType<pointData>("pointData");


    View w;
    w.setWindowTitle("Manipulator Controller  --By Hust ARMS");
    w.show();

    return a.exec();
}



