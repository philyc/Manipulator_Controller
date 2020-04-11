#ifndef WIDGET_H
#define WIDGET_H


//#include <QWidget>
//#include <QOpenGLFunctions_3_3_Core>
//#include <QOpenGLWidget>
//#include <QOpenGLShaderProgram>
//#include <QOpenGLTexture>
//#include <QTime>
//#include "shader.h"
//#include "model.h"
//#include <QtMath>
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

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget() override;

//protected:
//    void initializeGL() override;
//    void resizeGL(int w, int h) override;
//    void paintGL() override;

private:
    Ui::Widget *ui;

//    GLuint VBO, VAO;
//    Shader *ourShader;
//    QOpenGLTexture *texture1;
//    QOpenGLTexture *texture2;
//    QOpenGLFunctions_3_3_Core *core;
//    QTime time;
//    Model model;
//    GLuint lid1;
};
#endif // WIDGET_H
