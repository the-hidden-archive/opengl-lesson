#version 330 core

out vec4 FragColor;

uniform float uGreenColor;

void main()
{
    FragColor = vec4(0.f, uGreenColor, 0.f, 1.f);
}