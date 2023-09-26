#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


#include "debugOutput.h"


// glVertexAttribPointer - FUNCTION
        // (1) Shader variable position
        // (2) Amount of variables (ex: 3 floats)
        // (3) Specify data type
        // (4) Normalize (true) or do not normalize (false)
        // (5) stride - amount of bytes until next position, next color, or next texture. (ex: position -> 32 bytes -> position) 
        // (6) offset - amount of bytes from 1 type to the next (ex: position -> 12 bytes -> color)

class Drawer
{
public:
    unsigned int VBO, shapeVAO, lightSourceVAO, EBO;
    int bugPrinted = false;
    bool withEBO;

    Drawer
    (
        float vertices[],
        int verticesSize,
        bool passedEBO = false,
        unsigned int indices[] = { 0 },
        int indicesSize = 0
    ) 
    {
        withEBO = passedEBO;

        // bind the Vertex Array Object first

        //Shape VAO
        glGenVertexArrays(1, &shapeVAO);
        glBindVertexArray(shapeVAO);

        // bind vertex buffer object
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
        
        //Box Color
        setAttribPointer(0, 3, "float", false, 6, 0);

        // normal attribture
        setAttribPointer(1, 3, "float", false, 6, 3);

        //lightSource VAO
        glGenVertexArrays(1, &lightSourceVAO);
        glBindVertexArray(lightSourceVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //lightbox
        setAttribPointer(0, 3, "float", false, 6, 0);

        // bind element buffer object if it exists
        if (withEBO)
        {
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
        }

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
            typeSetter = GL_FLOAT;
        }

        if (!isNormalized)
        {
            normalizeSetter = GL_FALSE;
        }

        glVertexAttribPointer(position, variableAmount, typeSetter, normalizeSetter, strideMultiplier * sizeof(float), (void*)(offsetMultiplier * sizeof(float)));
        glEnableVertexAttribArray(position);
    }

    void useDrawArrays(int pickVAO = 0)
    {
        DebugOutput debugOutput(true);

        if (pickVAO == 1)
        {
            glBindVertexArray(shapeVAO);
        }
        else if (pickVAO == 2)
        {
            glBindVertexArray(lightSourceVAO);
        }
        else 
        {
            if (!bugPrinted) 
            {
                debugOutput.outputRedText("ERROR::NO_VAO_PICKED::[drawer.h]*FUNC:useDrawArray");
                bugPrinted = true;
            }
            
        }

        glBindVertexArray(shapeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void useDrawElements(int pickVAO = 0)
    {
        DebugOutput debugOutput(true);

        if (pickVAO == 1)
        {
            glBindVertexArray(shapeVAO);
        }
        else if (pickVAO == 2)
        {
            glBindVertexArray(lightSourceVAO);
        }
        else
        {
            if (!bugPrinted)
            {
                debugOutput.outputRedText("ERROR::NO_VAO_PICKED::[drawer.h]*FUNC:useDrawElements");
                bugPrinted = true;
            }
        }

        glBindVertexArray(shapeVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};


#endif