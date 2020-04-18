#include "resourcemanager.h"

std::map<QString, Shader> ResourceManager::map_Shaders;
std::map<QString, Texture2D> ResourceManager::map_Textures;

Shader ResourceManager::loadShader(const QString& name, const QString& vShaderFile, const QString& fShaderFile, const QString& gShaderfile){
  Shader shader;
  shader.compile(vShaderFile, fShaderFile, gShaderfile == NULL ? NULL : gShaderfile);
  map_Shaders[name] = shader;
  return map_Shaders[name];
}

Shader ResourceManager::getShader(const QString&  name){
  return map_Shaders[name];
}

Texture2D ResourceManager::loadTexture(const QString&  name, const QString& file, GLboolean alpha){
  Texture2D texture;

  if(alpha){
    texture.internal_format = QOpenGLTexture::RGBAFormat;
    texture.wrap_s = QOpenGLTexture::ClampToBorder; //在纹理的边界部分，没有任何处理。
    texture.wrap_t = QOpenGLTexture::ClampToBorder;
  }

  texture.generate(file);
  map_Textures[name] = texture;
  return texture;
}

Texture2D ResourceManager::getTexture(const QString&  name){
  return map_Textures[name];
}

void ResourceManager::clear(){
  for (std::map<QString, Shader>::iterator iter = map_Shaders.begin(); iter != map_Shaders.end(); ++iter)
    delete iter->second.shaderProgram;
  for (std::map<QString, Texture2D>::iterator iter = map_Textures.begin(); iter != map_Textures.end(); ++iter)
    delete iter->second.texture;

}
