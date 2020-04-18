#ifndef WIDGET_H
#define WIDGET_H


#include <QMainWindow>
#include "openglwidget.h"
#include <QVBoxLayout>
#include "shader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    OpenGLWidget* openGLWidget = new OpenGLWidget();


signals:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void test();



private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;


};
#endif // WIDGET_H
