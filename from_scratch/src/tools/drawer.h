#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debugOutput.h"

class Drawer
{
public:
    unsigned int VBO, VAO, EBO;
    bool withEBO;

    Drawer(float vertices[], int verticesSize, unsigned int indices[] = { 0 }, int indicesSize = 0, bool passedEBO = false, bool includeTexture = false) {
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

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texture attribute
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
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