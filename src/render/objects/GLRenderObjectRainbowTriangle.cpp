#include <GL/gl3w.h>

#include "GLRenderObject.hpp"
#include "GLRenderObjectRainbowTriangle.hpp"
#include "GLProgram.hpp"


GLRenderObjectRainbowTriangle::GLRenderObjectRainbowTriangle():
    GLRenderObject::GLRenderObject("RainbowTriangle", 1) // use GLProgram "RainbowTriangle", render w/ priority 1
{

}

void GLRenderObjectRainbowTriangle::Generate()
{
    float vertices[] = {
        // For visualization: each row is a vertex.
        // Each vertex has position [x, y, z] and color [r, g, b]
        -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,   // red color for this vertex
        0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,   // green color
        0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0,    // blue color for our top vertex
    };

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);  

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GLRenderObjectRainbowTriangle::Render()
{
    if (!m_renderEnabled) { return; }

    if (!m_geometryGenerated)
    {
        Generate();
        m_geometryGenerated = true;
    }
    GLTargetSetup(); // generic GLRenderObject.GLTargetSetup(), calls glUseProgram() and glUniformX()

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
