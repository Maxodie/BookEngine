#pragma once
#include "Graphics/Shaders/Shader.hpp"
#include "Graphics/Utilities/Data.h"

namespace Book
{
    struct PbrShader : Shader
    {
        BOOK_INLINE PbrShader(const std::string& filename)
            :   Shader(filename),
                u_NbrPointLight(glGetUniformLocation(m_ShaderID, "u_nbrPointLight")),
                u_ViewPos(glGetUniformLocation(m_ShaderID, "u_viewPos")),
                u_Roughness(glGetUniformLocation(m_ShaderID, "u_material.Roughness")),
                u_Metallic(glGetUniformLocation(m_ShaderID, "u_material.Metallic")),
                u_Albedo(glGetUniformLocation(m_ShaderID, "u_material.Albedo")),
                u_Model(glGetUniformLocation(m_ShaderID, "u_model")),
                u_View(glGetUniformLocation(m_ShaderID, "u_view")),
                u_Proj(glGetUniformLocation(m_ShaderID, "u_proj")) {}

        BOOK_INLINE void SetPointLight(PointLight& light, Transform3D& transform, int32_t index)
        {
            std::string intensity = "u_pointLights[" + std::to_string(index) + "].Intensity";
            std::string radiance = "u_pointLights[" + std::to_string(index) + "].Radiance";
            std::string position = "u_pointLights[" + std::to_string(index) + "].Position";

            uint32_t u_intensity = glGetUniformLocation(m_ShaderID, intensity.c_str());
            uint32_t u_radiance = glGetUniformLocation(m_ShaderID, radiance.c_str());
            uint32_t u_position = glGetUniformLocation(m_ShaderID, position.c_str());

            glUniform1f(u_intensity, light.Intensity);
            glUniform3fv(u_radiance, 1, &light.Radiance.x);
            glUniform3fv(u_position, 1, &transform.Translate.x);
        }

        BOOK_INLINE void SetuPointLightCount(int32_t count)
        {
            glUniform1i(u_NbrPointLight, count);
        }

        BOOK_INLINE void SetCamera(Camera3D& camera, Transform3D& transform, float ratio)
        {
            glUniformMatrix4fv(u_Proj, 1, GL_FALSE, glm::value_ptr(camera.Projection(ratio)));
            glUniformMatrix4fv(u_View, 1, GL_FALSE, glm::value_ptr(camera.View(transform)));
            glUniform3fv(u_ViewPos, 1, &transform.Translate.x);

        }

        BOOK_INLINE void Draw(Model3D& model, PbrMaterial& material, Transform3D& transform)
        {
            glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(transform.Matrix()));
            glUniform3fv(u_Albedo, 1, &material.Albedo.x);
            glUniform1f(u_Roughness, material.Roughness);
            glUniform1f(u_Metallic, material.Metallic);
            model->Draw(GL_TRIANGLES);
        }

    private:
        uint32_t u_NbrPointLight { 0 };
        uint32_t u_ViewPos { 0 };

        uint32_t u_Roughness { 0 };
        uint32_t u_Metallic { 0 };
        uint32_t u_Albedo { 0 };

        uint32_t u_Model { 0 };
        uint32_t u_View { 0 };
        uint32_t u_Proj { 0 };
    };
}
