#include "insertmodel.h"
#include <QFile>
//bool loadOBJ(const char *path, QVector<QVector3D> &out_positions, QVector<QVector2D> &out_uvs, QVector<QVector3D> &out_normals);
QOpenGLTexture *temp;

Model::Model(){
  core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

}

bool Model::init(const QString &path){
  /********** 更换模型时 删除上一个模型的数据 节约内存 ***********/
  for(int i = 0; i < objects.size(); ++i){
    core->glDeleteBuffers(1, &objects[i].positionVBO);
    core->glDeleteBuffers(1, &objects[i].uvVBO);
    core->glDeleteBuffers(1, &objects[i].normalVBO);
  }
  objects.clear();
  map_materials.clear();

  /*********** 初始化模型数据 ***************/
  bool res = loadOBJ(path);
  if(res){
    this->bindBufferData();
  }

  return res;
}

void Model::draw(GLboolean isOpenLighting){
  for(int i = 0; i < objects.size(); ++i){
    //
    ResourceManager::getShader("model").use().setVector3f("material.Ka", map_materials[objects[i].matName].Ka);
    ResourceManager::getShader("model").use().setBool("isOpenLighting", isOpenLighting);

    if(!map_materials.empty()){
      core->glActiveTexture(GL_TEXTURE0);
      ResourceManager::getTexture(map_materials[objects[i].matName].name_map_Ka).bind();
      if(isOpenLighting){
        //开启光照效果
        core->glActiveTexture(GL_TEXTURE1);
        ResourceManager::getTexture(map_materials[objects[i].matName].name_map_Kd).bind();
        ResourceManager::getShader("model").use().setVector3f("material.Kd", map_materials[objects[i].matName].Kd);
        ResourceManager::getShader("model").use().setVector3f("material.Ks", map_materials[objects[i].matName].Ks);
        ResourceManager::getShader("model").use().setFloat("material.shininess", map_materials[objects[i].matName].shininess);
      }
    }

    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, objects[i].positionVBO);
    core->glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );

    core->glEnableVertexAttribArray(1);
    core->glBindBuffer(GL_ARRAY_BUFFER, objects[i].uvVBO);
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    core->glEnableVertexAttribArray(2);
    core->glBindBuffer(GL_ARRAY_BUFFER, objects[i].normalVBO);
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  //绘图
    core->glDrawArrays(GL_TRIANGLES, 0, objects[i].positions.size());
  }
}

bool Model::loadOBJ(const QString &path){
  QFile file(path);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug()<<"OBJLOADER ERROR::FILE CAN NOT OPEN!";
    file.close();
    return false;
  }

  QTextStream in(&file);
  QString line;//文件流

  QVector<int> positionIndices, uvIndices, normalIndices;
  QVector<QVector3D> temp_positions;
  QVector<QVector2D> temp_uvs;
  QVector<QVector3D> temp_normals;
  QString temp_matName;//材质的名称

  while(!in.atEnd()){
    line = in.readLine();//读取一行,还有读取所有readAll();
    QStringList list = line.split(" ", QString::SkipEmptyParts);
    if(list.empty())
      continue;
    //qDebug() << list;
    if(list[0] == "mtllib"){//处理材质文件，即处理图片纹理
      /******* 1.1 处理材质文件路径 *********/
      //":/models/res/models/huapen/penzi.obj"
      QString mtl_path = path;
      int tempIndex = path.lastIndexOf("/")+1;
      mtl_path.remove(tempIndex, path.size()-tempIndex);//":/models/res/models/huapen/" 得到根目录路径，用来和材质文件名结合，生成正确路径
      //mtl_path += list[1];//得到材料路径":/models/res/models/huapen/penzi.mtl"
//      qDebug() << mtl_path;

      /******* 1.2 读取材质文件，导入Material类中 *********/
      QFile mtl_file(mtl_path+list[1]);//正确的材质文件路径
      if(!mtl_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"OBJLOADER ERROR::MTL_FILE CAN NOT OPEN!";
        mtl_file.close();
        file.close();
        return false;
      }
      QTextStream mtl_in(&mtl_file);
      QString mtl_line;//读取材质文件流的一行

      Material material;
      QString matName;//材质的名称
      while(!mtl_in.atEnd()){
        mtl_line = mtl_in.readLine();//读取一行,还有读取所有readAll();
        QStringList mtl_list = mtl_line.split(QRegExp("\\s+"), QString::SkipEmptyParts); //以“空格”与“\t”为识别符号，分开字符串
        if(mtl_list.empty())
          continue;
        if(mtl_list[0] == "newmtl"){
          matName = mtl_list[1];
          map_materials[matName] = material;
        }else if(mtl_list[0] == "Ns"){
          double shininess = mtl_list[1].toDouble();
          map_materials[matName].shininess = shininess;
        }else if(mtl_list[0] == "Ka"){
          double x = mtl_list[1].toDouble();
          double y = mtl_list[2].toDouble();
          double z = mtl_list[3].toDouble();

          QVector3D Ka(x, y, z);
          map_materials[matName].Ka = Ka;
        }else if(mtl_list[0] == "Kd"){
          double x = mtl_list[1].toDouble();
          double y = mtl_list[2].toDouble();
          double z = mtl_list[3].toDouble();

          QVector3D Kd(x, y, z);
          map_materials[matName].Kd = Kd;
        }else if(mtl_list[0] == "Ks"){
          double x = mtl_list[1].toDouble();
          double y = mtl_list[2].toDouble();
          double z = mtl_list[3].toDouble();

          QVector3D Ks(x, y, z);
          map_materials[matName].Ks = Ks;
        }else if(mtl_list[0] == "map_Ka"){
          ResourceManager::loadTexture(mtl_list[1], mtl_path+mtl_list[1]);
          map_materials[matName].name_map_Ka = mtl_list[1];
        }else if(mtl_list[0] == "map_Kd"){
          ResourceManager::loadTexture(mtl_list[1], mtl_path+mtl_list[1]);
          map_materials[matName].name_map_Kd = mtl_list[1];
        }
      }
     /******* 1.2 读取材质文件，导入Material类中 *********/
    }else if(list.size() > 1 && list[1] == "object"){//扫描寻找object
      if(!objects.empty()){
        for(int i=0; i < positionIndices.size(); i++ ){
          //得到索引
          int posIndex = positionIndices[i];
          int uvIndex = uvIndices[i];
          int norIndex = normalIndices[i];

          //根据索引取值
//          QVector3D pos = temp_positions[posIndex-1];
//          QVector2D uv = temp_uvs[uvIndex-1];
//          QVector3D nor = temp_normals[norIndex-1];
//qDebug() << uvIndex;
//          //存进object对象
//          objects.last().positions.push_back(pos);
//          objects.last().uvs.push_back(uv);
//          objects.last().normals.push_back(nor);
          //根据索引取值
          QVector3D pos = temp_positions[posIndex-1];
          objects.last().positions.push_back(pos);

          QVector3D nor = temp_normals[norIndex-1];
          objects.last().normals.push_back(nor);

          if(uvIndex != 0){
            QVector2D uv = temp_uvs[uvIndex-1];
            objects.last().uvs.push_back(uv);
          }

        }
        objects.last().matName = temp_matName;
        positionIndices.clear();
        uvIndices.clear();
        normalIndices.clear();
      }

      Object object;
      objects.push_back(object);//obj模型文件中的第一个object对象，因为一个obj模型可能还有多个object对象
    }else if (list[0] == "v"){
      double x = list[1].toDouble();
      double y = list[2].toDouble();
      double z = list[3].toDouble();

      QVector3D pos;
      pos.setX(x);
      pos.setY(y);
      pos.setZ(z);
      temp_positions.push_back(pos);
    }else if (list[0] == "vt"){
      double x = list[1].toDouble();
      double y = list[2].toDouble();

      QVector2D uv;
      uv.setX(x);
      uv.setY(y);
      temp_uvs.push_back(uv);
    }else if (list[0] == "vn"){
      double x = list[1].toDouble();
      double y = list[2].toDouble();
      double z = list[3].toDouble();

      QVector3D nor;
      nor.setX(x);
      nor.setY(y);
      nor.setZ(z);
      temp_normals.push_back(nor);
    }else if (list[0] == "usemtl"){
      temp_matName = list[1];
      //qDebug() << list[1];
    }else if (list[0] == "f"){
      if(list.size() > 4){
        qDebug() << "OBJLOADER ERROR::THE LOADER ONLY SUPPORT THE TRIANGLES MESH!" << endl;
        file.close();
        return false;
      }
      for(int i = 1; i < 4; ++i){//读取处理 f字符后边的 三长串字符，如“f 2396/2442/2376 101/107/111 100/106/110”
        QStringList slist = list[i].split("/");
        int posIndex = slist[0].toInt();
        int uvIndex = slist[1].toInt();
        int norIndex = slist[2].toInt();

        positionIndices.push_back(posIndex);
        uvIndices.push_back(uvIndex);
        normalIndices.push_back(norIndex);
        //qDebug() <<posIndex << " " << uvIndex << " " << norIndex;
      }
    }
  }

  //处理最后一个object

  for(int i=0; i < positionIndices.size(); i++ ){
    //得到索引
    int posIndex = positionIndices[i];
    int uvIndex = uvIndices[i];
    int norIndex = normalIndices[i];

    //根据索引取值
    QVector3D pos = temp_positions[posIndex-1];
    objects.last().positions.push_back(pos);

    QVector3D nor = temp_normals[norIndex-1];
    objects.last().normals.push_back(nor);

    if(uvIndex != 0){
      QVector2D uv = temp_uvs[uvIndex-1];
      objects.last().uvs.push_back(uv);
    }
            //qDebug() <<posIndex << " " << uvIndex << " " << norIndex;
  }
  objects.last().matName = temp_matName;

  file.close();
  return true;
}

void Model::bindBufferData(){
  for(int i = 0; i < objects.size(); ++i){
    core->glGenBuffers(1, &objects[i].positionVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, objects[i].positionVBO);
//    qDebug() << objects[i].positions.size();
    core->glBufferData(GL_ARRAY_BUFFER, objects[i].positions.size() * sizeof(QVector3D), &objects[i].positions[0], GL_STATIC_DRAW);

    core->glGenBuffers(1, &objects[i].uvVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, objects[i].uvVBO);
    core->glBufferData(GL_ARRAY_BUFFER, objects[i].uvs.size() * sizeof(QVector2D), &objects[i].uvs[0], GL_STATIC_DRAW);

    core->glGenBuffers(1, &objects[i].normalVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, objects[i].normalVBO);
    core->glBufferData(GL_ARRAY_BUFFER, objects[i].normals.size() * sizeof(QVector3D), &objects[i].normals[0], GL_STATIC_DRAW);
   // qDebug() << i << " : " << objects[i].positionVBO << " " << objects[i].uvVBO << " " << objects[i].normalVBO;
  }
}
