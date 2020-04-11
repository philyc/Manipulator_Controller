#ifndef SHADER_H
#define SHADER_H


#include <QDebug>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QString>



class Shader
{
public:
    Shader(const QString& vertexPath, const QString& fragmentPath);
    ~Shader();
    QOpenGLShaderProgram *shaderProgram;

    void use(){
        shaderProgram->bind();
    }

    //把设置着色器uniform变量操作写成Shader里的inline成员函数管理，真的方便很多。
    void setBool(const QString& name, const bool& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc,value);
    }

    void setInt(const QString& name, const GLint& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setFloat(const QString& name, const float& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setMat2(const QString& name, const QMatrix2x2& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setMat3(const QString& name, const QMatrix3x3& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setMat4(const QString& name, const QMatrix4x4& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }




};

#endif // SHADER_H
