#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

//#include "texture.h"
#include "shader.h"
#include <map>

    /// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};


class TextRenderer
{
public:
    std::map<GLchar, Character> Characters;
    // Constructor (inits shaders/shapes)
    TextRenderer(Shader& shader);
    // Destructor
    ~TextRenderer();
    // Renders a defined quad textured with given sprite
    void DrawText(std::string text
        , glm::vec2 position
        , float scale = 32.0f
        , glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Shader       shader;
    unsigned int VAO;
    unsigned int VBO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
    void initFreeType();
};
