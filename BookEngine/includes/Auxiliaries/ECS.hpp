#pragma once
#include <entt/entt.hpp>
#include "Graphics/Utilities/Data.h"
#include "Graphics/Models/Model.hpp"

namespace Book
{
    // typedefs
    using EntityID = entt::entity;
    using EntityRegistry = entt::registry;
    constexpr EntityID NENTT = entt::null;

    // transform component
    struct TransformComponent
    {
        BOOK_INLINE TransformComponent(const TransformComponent&) = default;
        BOOK_INLINE TransformComponent() = default;
        Transform3D Transform;
    };

    // camera component
    struct CameraComponent
    {
        BOOK_INLINE CameraComponent(const CameraComponent&) = default;
        BOOK_INLINE CameraComponent() = default;
        Camera3D Camera;
    };

    // common component
    struct EnttComponent
    {
        BOOK_INLINE EnttComponent(const EnttComponent&) = default;
        BOOK_INLINE EnttComponent() = default;
        std::string Name { "Untilted" };
    };

    // mesh component
    struct MeshComponent
    {
        BOOK_INLINE MeshComponent(const MeshComponent&) = default;
        BOOK_INLINE MeshComponent() = default;
        Mesh3D Mesh;
    };

    // model component
    struct ModelComponent
    {
        BOOK_INLINE ModelComponent(const ModelComponent&) = default;
        BOOK_INLINE ModelComponent() = default;
        Model3D Model;
    };

    struct Entity
    {
        BOOK_INLINE Entity(EntityRegistry* registry, EntityID entity)
            : m_Registry(registry), m_EnttID(entity) {}

        BOOK_INLINE Entity(EntityRegistry* registry)
            : m_Registry(registry), m_EnttID(m_Registry->create()) {}

        BOOK_INLINE virtual ~Entity() = default;
        BOOK_INLINE Entity() = default;

        BOOK_INLINE operator EntityID()
        {
            return m_EnttID;
        }

        BOOK_INLINE operator bool()
        {
            return m_Registry != nullptr && m_Registry->valid(m_EnttID);
        }

        BOOK_INLINE EntityID ID()
        {
            return m_EnttID;
        }

        // ++

        template<typename T, typename ... Args>
        BOOK_INLINE T& Attach(Args&&... args)
        {
            return m_Registry->get_or_emplace<T>(m_EnttID, std::forward<Args>(args)...);
        }

        template<typename T>
        BOOK_INLINE void Detach()
        {
            m_Registry->remove<T>(m_EnttID);
        }

        BOOK_INLINE void Destroy()
        {
            if(m_Registry)
            {
                m_Registry->destroy(m_EnttID);
            }
        }

        template<typename T>
        BOOK_INLINE bool Hat()
        {
            return m_Registry != nullptr && m_Registry->all_of<T>(m_EnttID);
        }

        template<typename T>
        BOOK_INLINE T& Get()
        {
            return m_Registry->get<T>(m_EnttID);
        }

    protected:
        EntityRegistry* m_Registry { nullptr };
        EntityID m_EnttID { NENTT };
    };
}
