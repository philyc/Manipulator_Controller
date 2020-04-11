#include "openglwidget.h"
#include <QDebug>
#include <QTimer>

OpenGLWidget::OpenGLWidget(QWidget *parent):QOpenGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget()
{

    makeCurrent();
    delete ourShader;
    core->glDeleteVertexArrays(1, &VAO);
    core->glDeleteBuffers(1, &VBO);
    texture1->destroy();
    texture2->destroy();
}

void OpenGLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    ourShader = new Shader("F:/computer/QT/test/opengl4/shader/vertexShader.vert", "F:/computer/QT/test/opengl3/shader/fragmentshader.frag");


    //    initializeOpenGLFunctions();
    //    // vertex shader
    //    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    //    vshader->compileSourceFile("://shader/vert.vert");
    //    // fragment shader
    //    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    //    fshader->compileSourceFile("://shader/frag.frag");


    //VAO，VBO数据部分
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    core->glGenVertexArrays(1, &VAO);//两个参数，第一个为需要创建的缓存数量。第二个为用于存储单一ID或多个ID的GLuint变量或数组的地址
    core->glGenBuffers(1, &VBO);

    core->glBindVertexArray(VAO);

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    core->glEnableVertexAttribArray(0);

    //    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //    core->glEnableVertexAttribArray(1);
    // texture coord attribute
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    core->glEnableVertexAttribArray(1);

    //    texture1 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/container.jpg").mirrored());
    //    texture1->setMinificationFilter(QOpenGLTexture::Nearest);
    //    texture1->setMagnificationFilter(QOpenGLTexture::Linear);
    //    texture1->setWrapMode(QOpenGLTexture::Repeat);
    texture1 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/container.jpg").mirrored(), QOpenGLTexture::GenerateMipMaps); //直接生成绑定一个2d纹理, 并生成多级纹理MipMaps
    if(!texture1->isCreated()){
        qDebug() << "Failed to load texture" << endl;
    }
    texture1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);// 等于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    texture1->setMinificationFilter(QOpenGLTexture::Linear);   //等价于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

    //第二张笑脸
    texture2 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/awesomeface.png").mirrored());

    //    texture2 = new QOpenGLTexture(QImage("F:/computer/QT/test/opengl4/texture/smile.png").mirrored()); //直接生成绑定一个2d纹理, 并生成多级纹理MipMaps
    if(!texture2->isCreated()){
        qDebug() << "Failed to load texture" << endl;
    }
    texture2->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);// 等于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture2->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    texture2->setMinificationFilter(QOpenGLTexture::Linear);   //等价于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture2->setMagnificationFilter(QOpenGLTexture::Linear);  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ourShader->use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);

    //开启计时器，返回毫秒
    time.start();

    //给着色器变量赋值
    QMatrix4x4 projection;
    // view.translate(QVector3D(0.0f, 0.0f, -3.0f));
    projection.perspective(45.0f, (GLfloat)width()/(GLfloat)height(), 0.1f, 100.0f);

    ourShader->use();
    //ourShader->setMat4("view", view);
    ourShader->setMat4("projection", projection);
    //开启状态
    core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    core->glEnable(GL_DEPTH_TEST);

    cameraPos = QVector3D(0.0f, 0.0f,  3.0f);
    cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
    cameraUp = QVector3D(0.0f, 1.0f,  0.0f);
    deltaTime = 0.0f;
    lastFrame = 0.0f;

    //    // shader program
    //    program = new QOpenGLShaderProgram;
    //    program->addShader(vshader);
    //    program->addShader(fshader);

    //    program->link();
    //    program->bind();

    //    view.setToIdentity();
    //    view.lookAt(QVector3D( 6, 0.5, 0), QVector3D( 6, 0.5, -6), QVector3D( 0, 1, 0));
    //    //1是眼睛的中心位置，2是眼睛看向的位置，3是眼睛的朝向位置

    //    // set color used to clear background
    //    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
    //    glEnable(GL_DEPTH_TEST);

    //    xtrans=0;ytrans=0;ztrans=0;//初始化坐标轴转动值
    //    glGenBuffers(3, handle);//在handle数组中返回当前n个未使用的名称，表示缓冲区对象

    //    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);//激活缓冲区对象，指定当前活动缓冲区的对象
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(terrian_pos), terrian_pos, GL_STATIC_DRAW);//用数据分配和初始化缓冲区对象

    //    //使设置在着色器中生效
    //    GLuint vPosition = program->attributeLocation("VertexPosition");
    //    glEnableVertexAttribArray(vPosition);
    //    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    //    glVertexAttribPointer( (GLuint)0, 3, GL_INT, GL_FALSE, 3*sizeof(GLint), 0 );//指定位置和偏移
    //    //glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat),  (const void *)(3*sizeof(GLfloat)) );//备用

    //    model.setToIdentity();
    //    glClearDepthf(1.0);
    //    glEnable(GL_TEXTURE_2D);
    //    //glEnable(GL_CULL_FACE);//是否使能正反面
    //    glDepthFunc(GL_LEQUAL);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    core->glViewport(0,0,w,h);
    //    glViewport(0,0,w/2,h/2);
    //    projection.setToIdentity();
    //    projection.perspective(60.0f, (GLfloat)w/(GLfloat)h, 0.001f, 100.0f);
}

QVector3D cubePositions[] = {       //为了省事，设为全局函数，若嫌封装性不好，改为成员变量指针，在initializeGL()重新赋值就好
                                    QVector3D( 0.0f,  0.0f,  -1.0f), //小小改动一下将z轴的0.0f变为-1.0f
                                    QVector3D( 2.0f,  5.0f, -15.0f),
                                    QVector3D(-1.5f, -2.2f, -2.5f),
                                    QVector3D(-3.8f, -2.0f, -12.3f),
                                    QVector3D( 2.4f, -0.4f, -3.5f),
                                    QVector3D(-1.7f,  3.0f, -7.5f),
                                    QVector3D( 1.3f, -2.0f, -2.5f),
                                    QVector3D( 1.5f,  2.0f, -2.5f),
                                    QVector3D( 1.5f,  0.2f, -1.5f),
                                    QVector3D(-1.3f,  1.0f, -1.5f)
                            };

void OpenGLWidget::paintGL()
{
    GLfloat currentFrame = (GLfloat)time.elapsed()/100;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    core->glActiveTexture(GL_TEXTURE0);
    texture1->bind();
    core->glActiveTexture(GL_TEXTURE1);
    texture2->bind();

    ourShader->use();



    QMatrix4x4 view;
//    GLfloat radius = 15.0f;
//    GLfloat camX = sin(((GLfloat)time.elapsed())/1000) * radius; //返回的毫秒太大了，除以1000小一些
//    GLfloat camZ = cos(((GLfloat)time.elapsed())/1000) * radius;
//    view.lookAt(QVector3D(camX, 0.0f, camZ), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    view.lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
    ourShader->setMat4("view", view);

    ourShader->setMat4("view", view);



    for(GLuint i = 0; i != 10; ++i){
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        model.rotate(20.0f * i, cubePositions[i]);//这里角度改为固定角度


        ourShader->setMat4("model", model);
        core->glBindVertexArray(VAO);
        core->glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    update();

    //    if(flag==0)//平移变化
    //    {

    //        //model.rotate(0, 0.0, 1.0, 0.0);
    //        model.translate(xtrans, ytrans, ztrans);//模型平移
    //        add_xtrans+=xtrans;
    //        add_ytrans+=ytrans;
    //        add_ztrans+=ztrans;
    //        model.rotate(yrot, 0.0, 1.0, 0.0);

    //    }else//旋转变化
    //    {
    //        model.setToIdentity();
    //        model.translate(6, 0.5, 0);//模型平移
    //        add_yrot+=yrot;
    //        model.rotate(add_yrot, 0.0, 1.0, 0.0);
    //        model.translate(add_xtrans-errorx, add_ytrans-errory, add_ztrans);//模型平移
    //    }
    //    flag=0;
    //    xtrans=0;
    //    ytrans=0;
    //    ztrans=0;
    //    yrot=0;
    //    program->setUniformValue("view", view);
    //    program->setUniformValue("projection", projection);
    //    program->setUniformValue("model", model);

    //    program->bind();
    //    //设置纹理
    //    QImage image(":/shader/texture_img.png");
    //    image = image.convertToFormat(QImage::Format_RGB888);
    //    image = image.mirrored();

    //    GLuint texture;
    //    glGenTextures(1, &texture);//glGenTextures的第一个参数是要创建的纹理数量，后面的参数就是保存这么多数量的整型数数组。

    //    glBindTexture(GL_TEXTURE_2D, texture);//绑定到OpenGL的环境里
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
    //                 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());//把加载的图片数据放到纹理中
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    //横坐标
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    //纵坐标
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//缩小时的过滤方式
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//放大时的过滤方式
    //    glGenerateMipmap(GL_TEXTURE_2D);//创建mipmaps,更流畅？

    //    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);//激活缓冲区对象，指定当前活动缓冲区的对象
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(terrian_texture), terrian_texture, GL_STATIC_DRAW);//用数据分配和初始化缓冲区对象
    //    GLuint m_texCoordAttr = program->attributeLocation("tempTextCoord");
    //    glEnableVertexAttribArray(m_texCoordAttr);
    //    //glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    //    glVertexAttribPointer( (GLuint)2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0 );//指定位置和偏移

    //    program->bind();
    //    //绘制，数目应该是一个面的顶点数x面数
    //    for(int s=0; s<img_width-2; s++)//z小于数据宽度w
    //    {
    //        glDrawElements(GL_TRIANGLE_STRIP, img_width*2, GL_UNSIGNED_INT, &terrian_index[img_width*s*2]);//索引应为数据宽度w,绘图数量应该是一层图像中面数x顶点数
    //    }
    //    qDebug()<<"paintGL";
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    GLfloat cameraSpeed = 1 * deltaTime;
    if(event->key() == Qt::Key_W){
        cameraPos += cameraFront * cameraSpeed;
    }
    if(event->key() == Qt::Key_S){
        cameraPos -= cameraFront * cameraSpeed;
    }
    if(event->key() == Qt::Key_A){
        cameraPos -= (QVector3D::crossProduct(cameraFront, cameraUp).normalized()) * cameraSpeed;
    }
    if(event->key() == Qt::Key_D){
        cameraPos += (QVector3D::crossProduct(cameraFront, cameraUp).normalized()) * cameraSpeed;
    }
    if(event->key() == Qt::Key_E){ //上升
        cameraPos += cameraUp * cameraSpeed;
    }
    if(event->key() == Qt::Key_Q){ //下降
        cameraPos -= cameraUp * cameraSpeed;
    }
}


//void OpenGLWidget::mousePressEvent(QMouseEvent *event)
//{
//    mousePos = QVector2D(event->pos());
//    event->accept();
//}

//void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    if(event->buttons() == Qt::LeftButton)
//    {
//        QVector2D newPos = (QVector2D)event->pos();
//        QVector2D diff = newPos - mousePos;
//        qreal angle = (diff.length())/3.6;
//        // Rotation axis is perpendicular to the mouse position difference
//        // vector
//        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
//        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
//        mousePos = newPos;
//        this->update();
//    }
//    event->accept();
//}

//void OpenGLWidget::wheelEvent(QWheelEvent *event)
//{
//    QPoint numDegrees = event->angleDelta() / 8;

//    if (numDegrees.y() > 0) {
//        ztrans += 0.25f;
//    } else if (numDegrees.y() < 0) {
//        ztrans -= 0.25f;
//    }
//    this->update();
//    event->accept();
//}


