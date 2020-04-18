#include "widget.h"
#include "ui_widget.h"
#include <math.h>


Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //为了便于让OpenGLWidget自动填充父窗口，这里为父窗口设置了一个布局
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->addWidget(openGLWidget);
    ui->openGLWidget->setLayout(centralLayout);
    connect(this,&Widget::keyPressEvent,openGLWidget,&OpenGLWidget::keyPressEvent);
    connect(this,&Widget::wheelEvent,openGLWidget,&OpenGLWidget::wheelEvent);

    connect(this,&Widget::test,openGLWidget,&OpenGLWidget::Moter1Run);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_pushButton_clicked()
{
    emit test();
}
