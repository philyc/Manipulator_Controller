#ifndef MODEL_H
#define MODEL_H
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>

class Model
{
public:
    Model();

    void SelectMaterial(int i);
    GLint Gen3DObjectList();
    void MyMaterial(GLenum mode, GLfloat * f, GLfloat alpha);
};

#endif // MODEL_H
