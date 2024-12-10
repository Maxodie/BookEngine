#pragma once
#include "Window/Window.hpp"
#include "Auxiliaries/ECS.hpp"
#include "Graphics/Renderer.hpp"

namespace Book
{
    // forward declaration
    struct AppInterface;

    // application context
    struct AppContext
    {
        BOOK_INLINE AppContext()
        {
            BOOK_CORE_INFO("App context creation started ...");
            Window = std::make_unique<AppWindow>(&Dispatcher, 1280, 720, "Empty Engine");
            Renderer = std::make_unique<GraphicsRenderer>(1280, 720);
            BOOK_CORE_INFO("App constext successfully created");
        }

        BOOK_INLINE ~AppContext()
        {
            for(auto& layer : Layers)
            {
                BOOK_DELETE(layer);
            }
        }

        std::unique_ptr<GraphicsRenderer> Renderer;
        std::vector<AppInterface*> Layers;
        std::unique_ptr<AppWindow> Window;
        EventDispatcher Dispatcher;
        EntityRegistry Scene;
    };
}
