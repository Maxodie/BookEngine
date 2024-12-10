#pragma once
#include "Graphics/Shaders/Shader.hpp"
#include "Graphics/Utilities/Data.h"

namespace Book
{
    struct PbrShader : Shader
    {
        BOOK_INLINE PbrShader(const std::string& filename)
            :   Shader(filename), u_Model(glGetUniformLocation(m_ShaderID, "u_model")),
                u_View(glGetUniformLocation(m_ShaderID, "u_view")),
                u_Proj(glGetUniformLocation(m_ShaderID, "u_proj")) {}

        BOOK_INLINE void SetCamera(Camera3D& camera, Transform3D& transform, float ratio)
        {
            glUniformMatrix4fv(u_Proj, 1, GL_FALSE, glm::value_ptr(camera.Projection(ratio)));
            glUniformMatrix4fv(u_View, 1, GL_FALSE, glm::value_ptr(camera.View(transform)));

        }

        BOOK_INLINE void Draw(Mesh3D& mesh, Transform3D& transform)
        {
            glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(transform.Matrix()));
            mesh->Draw(GL_TRIANGLES);
        }

        BOOK_INLINE void Draw(Model3D& model, Transform3D& transform)
        {
            glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(transform.Matrix()));
            model->Draw(GL_TRIANGLES);
        }

    private:
        uint32_t u_Model { 0 };
        uint32_t u_View { 0 };
        uint32_t u_Proj { 0 };
    };
}
