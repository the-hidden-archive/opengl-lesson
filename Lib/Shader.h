//
// Created by Пётр Смирнов on 17.01.2022.
//

#ifndef OPENGL_LESSON_SHADER_H
#define OPENGL_LESSON_SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
public:
    unsigned int ID; // shader program id
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setUInt(const std::string &name, unsigned int value) const;
};


#endif //OPENGL_LESSON_SHADER_H
