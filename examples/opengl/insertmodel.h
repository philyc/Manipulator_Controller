#ifndef INSERTMODEL_H
#define INSERTMODEL_H

#include <QOpenGLFunctions_3_3_Core>
#include <resourcemanager.h>
#include <QVector>

#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLTexture>
#include <QMap>

class Object;
class Material;

class Model
{
public:
  Model();
  bool init(const QString& path);
  void draw(GLboolean isOpenLighting = GL_FALSE);
private:
  bool loadOBJ(const QString& path);
  void bindBufferData();
  QOpenGLFunctions_3_3_Core *core;
  QVector<Object> objects;
  QMap<QString, Material> map_materials;

};

class Object{
public:
  GLuint positionVBO;
  GLuint uvVBO;
  GLuint normalVBO;

  QVector<QVector3D> positions;
  QVector<QVector2D> uvs;
  QVector<QVector3D> normals;

  QString matName;//材质名称
};

class Material{//一个简易的材质类
public:
  QVector3D Ka;//ambient反射系数
  QVector3D Kd;//diffuse反射系数
  QVector3D Ks;//specular反射系数
//  QOpenGLTexture* map_Ka;//环境反射贴图
//  QOpenGLTexture* map_Kd;//漫反射贴图
  double shininess;
  QString name_map_Ka;
  QString name_map_Kd;

};


#endif // INSERTMODEL_H
