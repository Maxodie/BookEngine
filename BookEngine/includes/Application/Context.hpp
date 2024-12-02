#pragma once
#include "Common/Event.hpp"

namespace Book
{
    // forward declaration
    struct AppInterface;

    // application context
    struct AppContext
    {
        BOOK_INLINE ~AppContext()
        {
            for(auto& layer : Layers)
            {
                BOOK_DELETE(layer);
            }
        }

        std::vector<AppInterface*> Layers;
        EventDispatcher Dispatcher;
    };
}
