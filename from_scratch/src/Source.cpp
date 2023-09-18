#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "windows.h";

#include "./tools/shader.h"
#include "./tools/drawer.h"
#include "./tools/texture.h"
#include "./tools/transform.h"

#include "./libraries/glm/glm.hpp"
#include "./libraries/glm/gtc/matrix_transform.hpp"
#include "./libraries/glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    glfwInit();

    // Tell GLFW the version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Only use core profile aka "modern functions"
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    // Error check window
    if (window == NULL)
    {
        std::cout << "ERROR::SOURCE::FAILED_CREATING_WINDOW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::SOURCE::FAILED_INITIALIZING_GLAD" << std::endl;
        return -1;
    }

    // Before Render Set up

    // Init Shader
    Shader ourShader("src/resources/shaders/shaderTexture.vert", "src/resources/shaders/shaderTexture.frag");

    // Init Texture
    Texture ourTexture("src/resources/textures/brick_wall.jpg");

    // Init vertex data

    float vertices[] = {
        // positions               // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Drawer draw(vertices, sizeof(vertices), indices, sizeof(indices), true, 3);   

    Transform transform(true);

    // render

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);


        // render
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw triangle
        ourTexture.use();
        ourShader.use();
        draw.use();

        // translate
        transform.setTranslate(0.0f, 0.5f, 0.0f);
        transform.setRotate(0.0f, 0.0f, 1.0f, 90.0f);
        transform.setScale(0.5f, 0.5f, 0.5f);
        transform.startTransform(ourShader, false, true, true);
        transform.resetTransform();

        // check and call events & swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}