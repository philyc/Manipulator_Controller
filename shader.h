#ifndef SHADER_H
#define SHADER_H


#include <QDebug>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QString>


class Shader   //配置着色器
{
public:
    Shader(const QString& vertexPath, const QString& fragmentPath);
    Shader();
    void compile(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource = nullptr);
    ~Shader();
    QOpenGLShaderProgram *shaderProgram;

    inline void use(){
        shaderProgram->bind();
    }

    inline void setBool(const QString& name, const bool& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc,value);
    }

    inline void setInt(const QString& name, const GLint& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    inline void setFloat(const QString& name, const float& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    inline void setMat2(const QString& name, const QMatrix2x2& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    inline void setMat3(const QString& name, const QMatrix3x3& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    inline void setMat4(const QString& name, const QMatrix4x4& value){
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

};

#endif // SHADER_H
