#include "color_renderer.h"
#include <iostream>


ColorRenderer::ColorRenderer(Shader& shader, float r, float g, float b)
{
    this->shader = shader;
    this->initRenderData(r, g, b);
}

ColorRenderer::~ColorRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void ColorRenderer::DrawColor(glm::vec2 position, glm::vec2 size, float rotate)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->shader.SetMatrix4("model", model);

    // render textured quad
    // this->shader.SetVector3f("ColorColor", color);

    //glActiveTexture(GL_TEXTURE0);
    //texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void ColorRenderer::initRenderData(float r, float g, float b)
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // color
        0.0f, 1.0f, r, g, b,
        1.0f, 0.0f, r, g, b,
        0.0f, 0.0f, r, g, b,

        0.0f, 1.0f, r, g, b,
        1.0f, 1.0f, r, g, b,
        1.0f, 0.0f, r, g, b
    };

    glGenVertexArrays(1, &this->quadVAO);
    glBindVertexArray(this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}