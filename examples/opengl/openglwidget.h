#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QOpenGLShader>
#include <iostream>
#include "shader.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTime>
#include "model.h"
#include <QtMath>

#define img_width 15
#define img_height 15

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
public:
    OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget() override;

    //键盘事件
    void keyPressEvent(QKeyEvent *event) override;

protected:

    //绘图三部曲
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;



    //    //鼠标事件
    //    void mousePressEvent(QMouseEvent *event);
    //    void mouseMoveEvent(QMouseEvent *event);
    //    void wheelEvent(QWheelEvent *event);



private:
    Shader *ourShader;
    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;
    QOpenGLFunctions_3_3_Core *core;
    QTime time;
    GLuint VBO, VAO;

    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;
    GLfloat deltaTime;
    GLfloat lastFrame;


    QTimer *timer;
};

#endif // OPENGLWIDGET_H
