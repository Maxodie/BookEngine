#pragma once
#include "Common/Core.hpp"

namespace Book
{
    template<typename Event>
    struct EventListener
    {
        using CallbackFn = std::function<void(const Event&)>;

        BOOK_INLINE EventListener(CallbackFn&& callback, uint32_t listenerID)
            : Callback(std::move(callback)), ID(listenerID)
        {}

        CallbackFn Callback;
        uint32_t ID;
    };

    // Event registry
    template<typename Event>
    struct EventRegistry
    {
        using Listener = std::unique_ptr<EventListener<Event>>;
        std::queue<std::unique_ptr<Event>> Queue;
        std::vector<Listener> Listeners;
    };

    // Event Dispatcher
    struct EventDispatcher
    {
        BOOK_INLINE ~EventDispatcher()
        {
            for(auto& [_, ptr] : m_Registry)
            {
                auto registry = CastRegistry<char>(ptr);
                BOOK_DELETE(registry);
            }
        }

        template<typename Event, typename Callback>
        BOOK_INLINE void AttachCallback(Callback&& callback, uint32_t listenerID)
        {
            auto listener = std::make_unique<EventListener<Event>>(std::move(callback), listenerID);
            GetRegistry<Event>()->Listeners.push_back(std::move(listener));
        }

        template<typename Event>
        BOOK_INLINE void DetachCallback(uint32_t listenerID)
        {
            auto& listeners = GetRegistry<Event>()->Listeners;
            listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                [&] (auto& listener)
                {
                    return (listener->ID == listenerID);
                }),
                listeners.end()
            );
        }

        BOOK_INLINE void EraseListener(uint32_t listenerID)
        {
            for(auto& [_, registry] : m_Registry)
            {
                auto& listeners = CastRegistry<char>(registry)->Listeners;
                listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                    [&] (auto& listener)
                    {
                        return (listener->ID == listenerID);
                    }),
                    listeners.end()
                );
            }
        }

        template<typename Event, typename... Args>
        BOOK_INLINE void PostEvent(Args&&... args)
        {
            auto registry = GetRegistry<Event>();
            if(registry->Listeners.empty())
            {
                return;
            }

            registry->Queue.push(std::make_unique<Event>(std::forward<Args>(args)...));
        }

        template<typename Task>
        BOOK_INLINE void PostTask(Task&& task)
        {
            m_Tasks.push(std::move(task));
        }

        BOOK_INLINE void PollEvents()
        {
            // Persistent callback
            for(auto& [_, ptr] : m_Registry)
            {
                auto registry = CastRegistry<char>(ptr);

                while(!registry->Queue.empty())
                {
                    for(auto& listener : registry->Listeners)
                    {
                        listener->Callback(*registry->Queue.front());
                    }
                    registry->Queue.pop();
                }
            }

            // Frame callback
            while(!m_Tasks.empty())
            {
                m_Tasks.front()();
                m_Tasks.pop();
            }
        }

    private:
        template<typename Event>
        BOOK_INLINE EventRegistry<Event>* CastRegistry(void* ptr)
        {
            return static_cast<EventRegistry<Event>*>(ptr);
        }

        template<typename Event>
        BOOK_INLINE EventRegistry<Event>* GetRegistry()
        {
            auto it = m_Registry.find(TypeID<Event>());
            if(it != m_Registry.end())
            {
                return CastRegistry<Event>(it->second);
            }
            auto registry = new EventRegistry<Event>();
            m_Registry[TypeID<Event>()] = registry;
            return registry;
        }

    private:
        std::unordered_map<uint32_t, void*> m_Registry;
        std::queue<std::function<void()>> m_Tasks;
    };
}
