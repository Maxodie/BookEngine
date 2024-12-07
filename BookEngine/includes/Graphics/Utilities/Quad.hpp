#pragma once
#include "Graphics/Buffers/Mesh.hpp"

namespace Book
{
    using Quad3D = std::unique_ptr<Mesh<ShadedVertex>>;
    using Quad2D = std::unique_ptr<Mesh<QuadVertex>>;

    // crate 2d quad Mesh
    BOOK_INLINE Quad2D CreateQuad2D()
    {
        MeshData<QuadVertex> data;

        data.Vertices = {
            {-1.0f, -1.0f, 0.0f, 0.0f },
            {-1.0f,  1.0f, 0.0f, 1.0f },
            { 1.0f,  1.0f, 1.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f, 0.0f }
        };

        data.Indices = {
            0, 1, 2,
            0, 2, 3
        };

        return std::make_unique<Mesh<QuadVertex>>(std::move(data));
    }

    // creates 3d quad mesh
    BOOK_INLINE Quad3D CreateQuad3D()
    {
        MeshData<ShadedVertex> data;
        data.Vertices.reserve(4);
        data.Indices.reserve(6);

        // add vertices to the MeshData stucture
        data.Vertices.emplace_back(
            glm::vec3(-0.5f, -0.5f, 0.0f), // bottom left
            glm::vec3(0.0f, 0.0f, 1.0f), // normal
            glm::vec2(0.0f, 0.0f) // UVs
        );

        data.Vertices.emplace_back(
            glm::vec2(0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f), // normal
            glm::vec2(1.0f, 0.0f) // UVs
        );

        data.Vertices.emplace_back(
            glm::vec3(0.5f, 0.5f, 0.0f), // bottom left
            glm::vec3(0.0f, 0.0f, 1.0f), // normal
            glm::vec2(1.0f, 0.0f) // UVs
        );

        data.Vertices.emplace_back(
            glm::vec3(-0.5f, 0.5f, 0.0f), // bottom left
            glm::vec3(0.0f, 0.0f, 1.0f), // normal
            glm::vec2(0.0f, 1.0f) // UVs
        );

        data.Indices.emplace_back(0); // tirangle : v0, v1, v2
        data.Indices.emplace_back(1);
        data.Indices.emplace_back(2);
        data.Indices.emplace_back(0); // triangle2 : v0, v2, v3
        data.Indices.emplace_back(2);
        data.Indices.emplace_back(3);

        return std::make_unique<Mesh<ShadedVertex>>(std::move(data));
    }
}
