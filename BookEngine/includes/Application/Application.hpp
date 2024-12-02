#pragma once
#include "Application/Interface.hpp"

namespace Book
{
    struct Application : AppInterface
    {
        BOOK_INLINE Application()
        {
            m_LayerID = TypeID<Application>();
            m_Context = new AppContext();
        }

        BOOK_INLINE ~Application()
        {
            BOOK_DELETE(m_Context);
        }

        BOOK_INLINE void RunContext()
        {
            while(true)
            {
                m_Context->Dispatcher.PollEvents();

                for(auto& layer : m_Context->Layers)
                {
                    layer->OnUpdate();
                }
            }
        }
    };
}
