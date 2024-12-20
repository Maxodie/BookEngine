#pragma once
#include "Graphics/Buffers/Mesh.hpp"

namespace Book
{
    // transform
    struct Transform3D
    {
        BOOK_INLINE glm::mat4 Matrix() const
        {
            return (glm::translate(glm::mat4(1.0f), Translate) *
                    glm::toMat4(glm::quat(glm::radians(Rotation))) *
                    glm::scale(glm::mat4(1.0f), Scale));
        }

        glm::vec3 Translate { glm::vec3(0.0f) };
        glm::vec3 Rotation { glm::vec3(0.0f) };
        glm::vec3 Scale { glm::vec3(1.0f) };
    };

    // camera
    struct Camera3D
    {
        BOOK_INLINE glm::mat4 Frustum(const Transform3D& transform, float ratio) const
        {
            return Projection(ratio) * View(transform);
        }

        BOOK_INLINE glm::mat4 View(const Transform3D& transform) const
        {
            return glm::lookAt(transform.Translate, (transform.Translate + glm::vec3(0, 0, -1)),
                               glm::vec3(0, 1, 0)) * glm::toMat4(glm::quat(glm::radians(transform.Rotation)));
        }

        BOOK_INLINE glm::mat4 Projection(float ratio) const
        {
            return glm::perspective(FOV, ratio, NearPlane, FarPlane);
        }

        float NearPlane { 0.3f };
        float FarPlane { 1000.0f };
        float FOV { 45.0f };
    };
}
