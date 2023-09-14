#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


#include "debugOutput.h"

class Drawer
{
public:
    unsigned int VBO, VAO, EBO;
    bool withEBO;

    Drawer
    (
        float vertices[],
        int verticesSize,
        unsigned int indices[] = { 0 },
        int indicesSize = 0,
        bool passedEBO = false,
        int numberOfAttributes = 1
    ) 
    {
        withEBO = passedEBO;

        // bind the Vertex Array Object first
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // bind vertex buffer object
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // bind element buffer object if it exists
        if (withEBO)
        {
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
        }

        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

        std::cout << sizeof(float) << " -test float" << std::endl;

        // glVertexAttribPointer
        // (1) Shader variable position
        // (2) Amount of variables (ex: 3 floats)
        // (3) Specify data type
        // (4) Normalize (true) or do not normalize (false)
        // (5) stride - amount of bytes until next position, next color, or next texture. (ex: position -> 32 bytes -> position) 
        // (6) offset - amount of bytes from 1 type to the next (ex: position -> 12 bytes -> color)
        
        //position attribute
        /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);*/
        setAttribPointer(0, 3, "float", false, 8, 0);

        //// color attribute
        /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);*/
        setAttribPointer(1, 3, "float", false, 8, 3);

        //// texture attribute
        //// texture coord attribute
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        //glEnableVertexAttribArray(2);
        setAttribPointer(2, 2, "float", false, 8, 6);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    void setAttribPointer
    (
        int position, 
        int variableAmount, 
        const char* variableType, 
        bool isNormalized, 
        int strideMultiplier,
        int offsetMultiplier
    )
    {
        GLfloat typeSetter;
        GLboolean normalizeSetter;

        if (variableType == "float")
        {
            std::cout << "TESTFLOAT" << std::endl;
            typeSetter = GL_FLOAT;
        }

        if (!isNormalized)
        {
            std::cout << "TESTFLOAT" << std::endl;
            normalizeSetter = GL_FALSE;
        }

        glVertexAttribPointer(position, variableAmount, typeSetter, normalizeSetter, strideMultiplier * sizeof(float), (void*)(offsetMultiplier * sizeof(float)));
        glEnableVertexAttribArray(position);
    }

    void use() 
    {
        glBindVertexArray(VAO);

        if (!withEBO)
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        else if (withEBO)
        {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
        }
        else
        {
            std::cout << "ERROR::DRAWER::DRAWING_SKIPPED::[tools/drawer.h]" << std::endl;
        }

    }
};


#endif