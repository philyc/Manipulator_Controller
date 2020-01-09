#include "view.h"
#include "controller.h"
#include "model.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    w.show();

    return a.exec();
}
