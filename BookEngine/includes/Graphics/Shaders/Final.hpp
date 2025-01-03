#pragma once
#include "Graphics/Shaders/Shader.hpp"
#include "Graphics/Utilities/Quad.hpp"

namespace Book
{
    struct FinalShader : Shader
    {
        BOOK_INLINE FinalShader(const std::string& filename)
            : Shader(filename), u_Map(glGetUniformLocation(m_ShaderID, "u_map")),
              m_Quad(CreateQuad2D()) {}

        BOOK_INLINE void SetSceneMap(uint32_t map)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, map);
            glUniform1i(u_Map, 0);
        }

        BOOK_INLINE void Show(uint32_t map)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(m_ShaderID);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, map);
            glUniform1i(u_Map, 0);
            m_Quad->Draw(GL_TRIANGLES);
            glUseProgram(0);
        }

    private:
        uint32_t u_Map { 0 };
        Quad2D m_Quad;
    };
}
