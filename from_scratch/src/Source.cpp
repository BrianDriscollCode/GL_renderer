#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "windows.h";

#include "./tools/shader.h"
#include "./tools/drawer.h"
#include "./tools/texture.h"
#include "./tools/transform.h"
#include "./tools/camera.h"
#include "./tools/materialType.h"

#include "./libraries/glm/glm.hpp"
#include "./libraries/glm/gtc/matrix_transform.hpp"
#include "./libraries/glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

int cameraWidth = 1280;
int cameraHeight = 720;

float SPEED = 0.1f;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

float xPos = 0.0f;
float yPos = 0.0f;
float zPos = 0.0f;

int main()
{
    glfwInit();

    // Tell GLFW the version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Only use core profile aka "modern functions"
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window object
    GLFWwindow* window = glfwCreateWindow(cameraWidth, cameraHeight, "LearnOpenGL", NULL, NULL);
    // Error check window
    if (window == NULL)
    {
        std::cout << "ERROR::SOURCE::FAILED_CREATING_WINDOW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::SOURCE::FAILED_INITIALIZING_GLAD" << std::endl;
        return -1;
    }

    // configure global state for openGL
    glEnable(GL_DEPTH_TEST);

    // Before Render Set up

    // Init Shaders
    Shader lightingShader("src/resources/shaders/lightingShader.vert", "src/resources/shaders/lightingShader.frag");
    Shader lightCubeShader("src/resources/shaders/lightBoxShader.vert", "src/resources/shaders/lightBoxShader.frag");
    MaterialType material(true);


    // Init Texture
    Texture ourTexture("src/resources/textures/brick_wall.jpg");

    // Init vertex data
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    //Drawer draw(vertices, sizeof(vertices), indices, sizeof(indices), false, 3);   

    Drawer draw(vertices, sizeof(vertices));
    Transform transform(true);
    glm::mat4 initCamera = glm::mat4(1.0f);
    Camera camera(initCamera, initCamera, initCamera, cameraPos);
    
    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };



    // render

   glm::vec3 lightPos(-1.0f, 0.0f, -5.0f);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);


        // render
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // init textures and shaders
        ourTexture.use();
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", camera.position);
        lightingShader.setVec3("material.ambient", material.gold.ambient);
        lightingShader.setVec3("material.diffuse", material.gold.diffuse);
        lightingShader.setVec3("material.specular", material.gold.specular);
        lightingShader.setFloat("material.shininess", material.gold.shininess);
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        lightingShader.setVec3("light.ambient", material.minimal.ambient);
        lightingShader.setVec3("light.diffuse", material.minimal.diffuse);
        lightingShader.setVec3("light.specular", material.minimal.specular);

        // init Camera values for 1st shader
        camera.setProjection(lightingShader, cameraWidth, cameraHeight);
        camera.setViewLookAt(lightingShader, cameraPos, cameraFront, cameraUp);

        for (int i = 0; i < 10; i++)
        {
            // init model
            camera.use(lightingShader, cubePositions[i], i);

            // draw shapes
            draw.useDrawArrays(1);
        }

        lightCubeShader.use();
        //init camera values for 2nd shader
        camera.setProjection(lightCubeShader, cameraWidth, cameraHeight);
        camera.setViewLookAt(lightCubeShader, cameraPos, cameraFront, cameraUp);
        camera.use(lightCubeShader, lightPos, 1, true);

        lightPos.x -= sin(glfwGetTime() * 2.25f) * 0.25f;
        //lightPos.y -= sin(glfwGetTime()) * 0.25f;

        // draw light object
        draw.useDrawArrays(2);
       
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_F8) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += SPEED * cameraFront;

    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= SPEED * cameraFront;
    }
    else
    {
        zPos = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * SPEED;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * SPEED;
    }
    else
    {
        xPos = 0.0f;
    }
    cameraPos.y = 0.0f;
    
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

}