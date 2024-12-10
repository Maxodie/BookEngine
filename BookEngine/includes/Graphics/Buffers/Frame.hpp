#pragma once
#include "Common/Core.hpp"

namespace Book
{
    struct FrameBuffer
    {
        BOOK_INLINE FrameBuffer(int32_t width, int32_t height)
            : m_Width(width), m_Height(height)
        {
            glGenFramebuffers(1, &m_BufferID);
            glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

            CreateColorAttachment();
            CreateRenderBuffer();

            // attachment targets
            uint32_t attachments[1] {
                GL_COLOR_ATTACHMENT0
            };

            glDrawBuffers(1, attachments);

            // check frame buffer
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                BOOK_CORE_ERROR("glCheckFramebufferStatus() failed!");
            }

            // unbind frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        BOOK_INLINE ~FrameBuffer()
        {
            glDeleteTextures(1, &m_Color);
            glDeleteRenderbuffers(1, &m_Render);
            glDeleteFramebuffers(1, &m_BufferID);
        }

        BOOK_INLINE float Ratio()
        {
            return m_Width/static_cast<float>(m_Height);
        }

        BOOK_INLINE void Resize(int32_t width, int32_t height)
        {
            // update size
            m_Width = width;
            m_Height = height;

            //resize color attachment
            glBindTexture(GL_TEXTURE_2D, m_Color);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F,
                         m_Width, m_Height, 0,
                         GL_RGBA, GL_FLOAT, NULL);
            glBindTexture(GL_TEXTURE_2D, 0);

            // resize depth attachment
            glBindRenderbuffer(GL_RENDERBUFFER, m_Render);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                                   m_Width, m_Height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        BOOK_INLINE uint32_t GetTexture()
        {
            return m_Color;
        }

        BOOK_INLINE void Begin()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
            glViewport(0, 0, m_Width, m_Height);
            glClearColor(0, 0, 0, 1);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_SAMPLES);
        }

        BOOK_INLINE void End()
        {
            glDisable(GL_SAMPLES);
            glDisable(GL_DEPTH_TEST);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

    private:
        BOOK_INLINE void CreateColorAttachment()
        {
            glGenTextures(1, &m_Color);
            glBindTexture(GL_TEXTURE_2D, m_Color);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color, 0);
        }

        BOOK_INLINE void CreateRenderBuffer()
        {
            glGenRenderbuffers(1, &m_Render);
            glBindRenderbuffer(GL_RENDERBUFFER, m_Render);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Width, m_Height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Render);
        }

    private:
        uint32_t m_BufferID {0};
        uint32_t m_Render {0};
        uint32_t m_Color {0};
        int32_t m_Height {0};
        int32_t m_Width {0};
    };
}
