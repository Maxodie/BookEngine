#pragma once
#include "Window/Inputs.hpp"

namespace Book
{
    struct GraphicsRenderer
    {
        BOOK_INLINE GraphicsRenderer(int32_t width, int32_t height)
        {
            if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                BOOK_CORE_FATAL("Failed to init glad!");
                exit(EXIT_FAILURE);
            }

        }
    };
}
