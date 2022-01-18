#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "Lib/Shader.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Hello, OpenGL"

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height); // call when window was resized
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z , 1.0f);\n"
                                 "}";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.f, 0.5f, 0.2f, 1.f);\n"
                                   "}";

const float vertices[] = {
        0.5f, 0.5f, 0.f,
        -0.5f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f
};

unsigned char indices[] = {
        0, 1, 2,
        3, 0, 2
};

int main()
{
    glfwInit();

    // set some params for window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // setup window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if(window == nullptr){
        std::cerr << "Fatal Error: window was not initialize" << std::endl;
        glfwTerminate();
        return -1;
    }

    // setup current context for OpenGL
    glfwMakeContextCurrent(window);

    // try glad for errors
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cerr << "Fatal Error: GLAD was not work" << std::endl;
        glfwTerminate();
        return -1;
    }

    // setup viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // setup callbacks
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);

    // create a triangle objects
    // VBO (Vertex Buffer Objects) and VAO

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    // bind VBO and VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // setup VBO data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // shaders
    Shader sampleShader("Assets/Shaders/SampleTriangle/triangle.vert", "Assets/Shaders/SampleTriangle/triangle.frag");

    // setup shader program attribs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glClearColor(1.f, 1.f, 1.f, 1.f);

    // rendering
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        // here is rendering
        glClear(GL_COLOR_BUFFER_BIT);

        sampleShader.use();
        sampleShader.setFloat("uGreenColor", (float)sin(glfwGetTime())/2+0.5f);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}