#pragma once
#include "Window/Window.hpp"

namespace Book
{
    // forward declaration
    struct AppInterface;

    // application context
    struct AppContext
    {
        BOOK_INLINE AppContext()
        {
            Window = std::make_unique<AppWindow>(&Dispatcher, 1280, 720, "Empty Engine");
        }

        BOOK_INLINE ~AppContext()
        {
            for(auto& layer : Layers)
            {
                BOOK_DELETE(layer);
            }
        }

        std::vector<AppInterface*> Layers;
        std::unique_ptr<AppWindow> Window;
        EventDispatcher Dispatcher;
    };
}
