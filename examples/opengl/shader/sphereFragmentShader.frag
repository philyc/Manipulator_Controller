#version 330 core
out vec4 FragColor;
uniform float uR; //球半径

in vec3 vPosition;

void main(void)
{
    vec3 color;
    float n = 8.0; //x、y、z轴的分块数量
    float span = 2.0 * uR / n; //每块长度
    int i = int((vPosition.x + uR) / span); x轴所在层数
    int j = int((vPosition.y + uR) / span); y轴所在层数
    int k = int((vPosition.z + uR) / span); z轴所在层数
    int whichColor = int(mod(float(i+j+k),2.0)); //根据行列数取余，决定颜色
    if(whichColor == 1){
        color = vec3(0.678,0.231,0.129);
    }else{
        color = vec3(1.0,1.0,1.0);
    }
    fragColor = vec4(color,0);
}