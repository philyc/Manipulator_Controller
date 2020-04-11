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
}

Widget::~Widget()
{
    delete ui;
}





//#include "widget.h"
//#include "ui_widget.h"

//Widget::Widget(QWidget *parent)
//    : ui(new Ui::Widget)
//{
//    ui->setupUi(this);
//    this->setWindowTitle("test");
//}

//Widget::~Widget()
//{
//    makeCurrent();
//    delete ourShader;
//    core->glDeleteVertexArrays(1, &VAO);
//    core->glDeleteBuffers(1, &VBO);
//    texture1->destroy();
//    texture2->destroy();

//    delete ui;
//}

//void Widget::initializeGL(){
//    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
//    ourShader = new Shader("F:/computer/QT/test/opengl4/shader/vertexShader.vert", "F:/computer/QT/test/opengl3/shader/fragmentshader.frag");


//    //VAO，VBO数据部分
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };

//    core->glGenVertexArrays(1, &VAO);//两个参数，第一个为需要创建的缓存数量。第二个为用于存储单一ID或多个ID的GLuint变量或数组的地址
//    core->glGenBuffers(1, &VBO);

//    core->glBindVertexArray(VAO);

//    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    core->glEnableVertexAttribArray(0);

//    //    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    //    core->glEnableVertexAttribArray(1);
//    // texture coord attribute
//    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    core->glEnableVertexAttribArray(1);

//    //    texture1 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/container.jpg").mirrored());
//    //    texture1->setMinificationFilter(QOpenGLTexture::Nearest);
//    //    texture1->setMagnificationFilter(QOpenGLTexture::Linear);
//    //    texture1->setWrapMode(QOpenGLTexture::Repeat);
//    texture1 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/container.jpg").mirrored(), QOpenGLTexture::GenerateMipMaps); //直接生成绑定一个2d纹理, 并生成多级纹理MipMaps
//    if(!texture1->isCreated()){
//        qDebug() << "Failed to load texture" << endl;
//    }
//    texture1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);// 等于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    texture1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//    texture1->setMinificationFilter(QOpenGLTexture::Linear);   //等价于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

//    //第二张笑脸
//    texture2 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/awesomeface.png").mirrored());

//    //    texture2 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/smile.png").mirrored()); //直接生成绑定一个2d纹理, 并生成多级纹理MipMaps
//    if(!texture2->isCreated()){
//        qDebug() << "Failed to load texture" << endl;
//    }
//    texture2->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);// 等于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    texture2->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//    texture2->setMinificationFilter(QOpenGLTexture::Linear);   //等价于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    texture2->setMagnificationFilter(QOpenGLTexture::Linear);  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    ourShader->use();
//    ourShader->setInt("texture1", 0);
//    ourShader->setInt("texture2", 1);

//    //开启计时器，返回毫秒
//    time.start();

//    //给着色器变量赋值
//    QMatrix4x4 projection;
//    // view.translate(QVector3D(0.0f, 0.0f, -3.0f));
//    projection.perspective(45.0f, (GLfloat)width()/(GLfloat)height(), 0.1f, 100.0f);

//    ourShader->use();
//    //ourShader->setMat4("view", view);
//    ourShader->setMat4("projection", projection);
//    //开启状态
//    core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    core->glEnable(GL_DEPTH_TEST);

//}

//void Widget::resizeGL(int w, int h){
//    core->glViewport(0,0,w,h);
//}

//QVector3D cubePositions[] = {       //为了省事，设为全局函数，若嫌封装性不好，改为成员变量指针，在initializeGL()重新赋值就好
//                                    QVector3D( 0.0f,  0.0f,  -1.0f), //小小改动一下将z轴的0.0f变为-1.0f
//                                    QVector3D( 2.0f,  5.0f, -15.0f),
//                                    QVector3D(-1.5f, -2.2f, -2.5f),
//                                    QVector3D(-3.8f, -2.0f, -12.3f),
//                                    QVector3D( 2.4f, -0.4f, -3.5f),
//                                    QVector3D(-1.7f,  3.0f, -7.5f),
//                                    QVector3D( 1.3f, -2.0f, -2.5f),
//                                    QVector3D( 1.5f,  2.0f, -2.5f),
//                                    QVector3D( 1.5f,  0.2f, -1.5f),
//                                    QVector3D(-1.3f,  1.0f, -1.5f)
//                            };

//void Widget::paintGL(){
//    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    core->glActiveTexture(GL_TEXTURE0);
//    texture1->bind();
//    core->glActiveTexture(GL_TEXTURE1);
//    texture2->bind();

//    ourShader->use();



//    QMatrix4x4 view;
//    GLfloat radius = 15.0f;
//    GLfloat camX = sin(((GLfloat)time.elapsed())/1000) * radius; //返回的毫秒太大了，除以1000小一些
//    GLfloat camZ = cos(((GLfloat)time.elapsed())/1000) * radius;
//    view.lookAt(QVector3D(camX, 0.0f, camZ), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
//    ourShader->setMat4("view", view);



//    for(GLuint i = 0; i != 10; ++i){
//        QMatrix4x4 model;
//        model.translate(cubePositions[i]);
//        model.rotate(20.0f * i, cubePositions[i]);//这里角度改为固定角度


//        ourShader->setMat4("model", model);
//        core->glBindVertexArray(VAO);
//        core->glDrawArrays(GL_TRIANGLES, 0, 36);
//    }

//    update();

//}
