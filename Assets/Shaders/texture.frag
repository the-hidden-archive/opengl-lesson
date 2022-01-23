#version 330 core

in vec3 fColor;
in vec2 fTexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main(){
    FragColor = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.2);
}