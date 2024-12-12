#pragma once
#include "Auxiliaries/ECS.hpp"

namespace Book
{
    struct AppInterface
    {
        BOOK_INLINE virtual ~AppInterface() = default;

        template<typename Layer>
        BOOK_INLINE Layer* GetLayer()
        {
            BOOK_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);
            auto itr = std::find_if(m_Context->Layers.begin(),
            m_Context->Layers.end(), [this] (auto layer)
            {
                return (layer->m_LayerID == TypeID<Layer>());
            });

            if(itr != m_Context->Layers.end())
            {
                return static_cast<Layer*>(*itr);
            }
            return nullptr;
        }

        template<typename Layer, typename... Args>
        BOOK_INLINE Layer* AttachLayer(Args&&... args)
        {
            BOOK_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);

            if(GetLayer<Layer>() != nullptr)
            {
                BOOK_CORE_ERROR("Layer already attached");
                return nullptr;
            }

            Layer* layer { new Layer(std::forward<Args>(args)...) };
            m_Context->Layers.push_back(layer);
            layer->m_LayerID = TypeID<Layer>();
            layer->m_Context = m_Context;
            layer->OnStart();
            return layer;
        }

        template<typename Layer>
        BOOK_INLINE void DetachLayer()
        {
            BOOK_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);
            m_Context->Dispatcher.PostTask([this]
            {
                m_Context->Layers.erase(std::remove_if(m_Context->Layers.begin(), m_Context->Layers.end(), [this](auto& layer)
                    {
                        if(layer->m_LayerID == TypeID<Layer>())
                        {
                            m_Context->Dispatcher.EraseListener(layer->m_LayerID);
                            BOOK_DELETE(layer);
                            return true;
                        }
                        return false;
                    }),
                m_Context->Layers.end());
            });
        }

        // attach event callback
        template<typename Event, typename Callback>
        BOOK_INLINE void AttachCallback(Callback&& callback)
        {
            m_Context->Dispatcher.AttachCallback<Event>(std::move(callback), m_LayerID);
        }

        // post event
        template<typename Event, typename... Args>
        BOOK_INLINE void PostEvent(Args&&... args)
        {
            m_Context->Dispatcher.PostEvent<Event>(std::forward(args)...);
        }

        // post task event
        template<typename Task>
        BOOK_INLINE void PostTask(Task&& task)
        {
            m_Context->Dispatcher.PostTask(std::move(task));
        }

         // post event
        template<typename Event>
        BOOK_INLINE void DetachCallback()
        {
            m_Context->Dispatcher.DetachCallback<Event>(m_LayerID);
        }

        template<typename Entt, typename... Args>
        BOOK_INLINE Entt CreateEntt(Args... args)
        {
            BOOK_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&m_Context->Scene, std::forward(args)...));
        }

        template<typename Entt>
        BOOK_INLINE Entt ToEntt(EntityID entity)
        {
            BOOK_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&m_Context->Scene, entity));
        }

        template<typename Entt, typename Comp, typename Task>
        BOOK_INLINE void EnttView(Task&& task)
        {
            BOOK_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            m_Context->Scene.view<Comp>().each([this, &task] (auto entity, auto& comp)
            {
                task(std::move(Entt(&m_Context->Scene, entity)), comp);
            });
        }

    protected:
        BOOK_INLINE virtual void OnUpdate() {}
        BOOK_INLINE virtual void OnStart() {}

    private:
        friend struct Application;
        AppContext* m_Context;
        uint32_t m_LayerID;
    };

}
