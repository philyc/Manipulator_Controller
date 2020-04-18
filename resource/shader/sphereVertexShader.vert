#version 330 core
layout (location = 0) in vec3 aPos;
smooth out vec3 vPosition; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vPosition = aPosition;
}



#version 330
uniform mat4 uPMatrix,camMatrix,uMMatrix;
layout (location = 0) in vec3 aPosition;
smooth out vec3 vPosition; //将顶点坐标传递给片元着色器
 
void main(void)
{
    gl_Position = uPMatrix * camMatrix *uMMatrix * vec4(aPosition,1);
    vPosition = aPosition;
}