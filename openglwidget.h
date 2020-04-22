#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#ifndef PI2
#define PI2 6.2831853//2PI
#endif

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
#include <QtMath>
#include <QDebug>
#include <QTimer>
#include "model.h"

class OpenGLWidget: public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget() override;

    //键盘事件
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

protected:

    //绘图三部曲
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    //鼠标事件
    void mouseMoveEvent(QMouseEvent *event) override;

private:

    Shader *recShader,*sphShader;
    QOpenGLTexture *texture1;
    QOpenGLTexture *texture2;
    QOpenGLFunctions_3_3_Core *core;
    QTime time;

    //    GLuint VBO, VAO;
    GLuint VBO[2], VAO[2];
    QVector<GLfloat> m_points;

    //控制视角变化
    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;
    GLfloat deltaTime;
    GLfloat lastFrame;

    //控制鼠标变化
    GLboolean firstMouse;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat lastX;
    GLfloat lastY;
    GLfloat fov;

    QTimer *timer;

};

#endif // OPENGLWIDGET_H
