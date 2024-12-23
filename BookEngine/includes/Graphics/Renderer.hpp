#pragma once
#include "Window/Inputs.hpp"
#include "Graphics/Buffers/Frame.hpp"
#include "Graphics/Shaders/PBR.hpp"
#include "Graphics/Shaders/Final.hpp"

namespace Book
{
    struct GraphicsRenderer
    {
        BOOK_INLINE GraphicsRenderer(int32_t width, int32_t height)
        {
            BOOK_CORE_INFO("GraphicsRenderer creation started ...");
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                BOOK_CORE_FATAL("Failed to init glad!");
                exit(EXIT_FAILURE);
            }

            m_FinalShader = std::make_unique<FinalShader>("Resources/Shaders/final.glsl");
            m_PbrShader = std::make_unique<PbrShader>("Resources/Shaders/pbr.glsl");
            m_Frame = std::make_unique<FrameBuffer>(width, height);

            BOOK_CORE_INFO("GraphicsRenderer successfully created");
        }

        BOOK_INLINE void SetPointLight(PointLight& light, Transform3D& transform, uint32_t index)
        {
            m_PbrShader->SetPointLight(light, transform, index);
        }

        BOOK_INLINE void SetPointLightCount(int32_t count)
        {
            m_PbrShader->SetuPointLightCount(count);
        }

        BOOK_INLINE void SetCamera(Camera3D& camera, Transform3D& transform)
        {
            m_PbrShader->SetCamera(camera, transform, m_Frame->Ratio());
        }

        BOOK_INLINE void Draw(Model3D& model, PbrMaterial& material, Transform3D& transform)
        {
            m_PbrShader->Draw(model, material, transform);
        }

        BOOK_INLINE void Resize(int32_t width, int32_t height)
        {
            m_Frame->Resize(width, height);
        }

        BOOK_INLINE uint32_t GetFrame()
        {
            return m_Frame->GetTexture();
        }

        BOOK_INLINE void NewFrame()
        {
            m_Frame->Begin();
            m_PbrShader->Bind();
        }

        BOOK_INLINE void EndFrame()
        {
            m_PbrShader->Unbind();
            m_Frame->End();
        }

        BOOK_INLINE void ShowFrame()
        {
            m_FinalShader->Show(m_Frame->GetTexture());
        }

    private:
        std::unique_ptr<FrameBuffer> m_Frame;
        std::unique_ptr<FinalShader> m_FinalShader;
        std::unique_ptr<PbrShader> m_PbrShader;
    };
}
