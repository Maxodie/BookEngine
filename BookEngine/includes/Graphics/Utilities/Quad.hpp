#pragma once
#include "Graphics/Buffers/Mesh.hpp"

namespace Book
{
    using Quad3D = std::unique_ptr<Mesh<ShadedVertex>>;
    using Quad2D = std::unique_ptr<Mesh<QuadVertex>>;

    // crate 2d quad Mesh
    BOOK_INLINE Quad2D CreateQuad2D()
    {
        MeshData<QuadVertex> data{
            .Indices {
                0, 1, 2,
                0, 2, 3
            },

            .Vertices{
                {-1.0f, -1.0f, 0.0f, 0.0f },
                {-1.0f,  1.0f, 0.0f, 1.0f },
                { 1.0f,  1.0f, 1.0f, 1.0f },
                { 1.0f, -1.0f, 1.0f, 0.0f }
            }
        };

        return std::make_unique<Mesh<QuadVertex>>(std::move(data));
    }

    // creates 3d quad mesh
    BOOK_INLINE Quad3D CreateQuad3D()
    {
        MeshData<ShadedVertex> data;
        data.Vertices.reserve(4);
        data.Indices.reserve(6);

        // define vertices for quad
        constexpr glm::vec3 normal(0.0f, 0.0f, 1.0f); // Normal vector for all vertices

        // Define vertices for quad
        data.Vertices = {
            { .Position { glm::vec3(-0.5f, -0.5f, 0.0f) }, .Normal { normal }, .UVs { glm::vec2(0.0f, 0.0f) } },
            { .Position { glm::vec3(0.5f, -0.5f, 0.0f) }, .Normal { normal }, .UVs { glm::vec2(1.0f, 0.0f) } },
            { .Position { glm::vec3(0.5f, 0.5f, 0.0f) }, .Normal { normal }, .UVs { glm::vec2(1.0f, 1.0f) } },
            { .Position { glm::vec3(-0.5f, 0.5f, 0.0f) }, .Normal { normal }, .UVs { glm::vec2(0.0f, 1.0f) } }
        };

        // Define indices for two triangles
        data.Indices = {0, 1, 2, 0, 2, 3};
        // add vertices to the MeshData stucture
        // tirangle : v0, v1, v2 | triangle2 : v0, v2, v3
        data.Indices = { 0, 1, 2, 0, 2, 3};

        return std::make_unique<Mesh<ShadedVertex>>(std::move(data));
    }
}
