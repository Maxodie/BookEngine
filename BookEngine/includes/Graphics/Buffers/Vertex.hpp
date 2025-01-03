#pragma once
#include "Common/Core.hpp"

namespace Book
{
    // quad vertex
    struct QuadVertex
    {
        float Data[4] {0.0f, 0.0f, 0.0f, 0.0f};
    };

    // flat vertex
    struct FlatVertex
    {
        glm::vec3 Position { glm::vec3(0.0f) };
        glm::vec4 Color { glm::vec4(0.0f) };
    };

    // shading vertex
    struct ShadedVertex
    {
        glm::vec3 Position { glm::vec3(0.0f) };
        glm::vec3 Normal { glm::vec3(0.0f) };
        glm::vec2 UVs { glm::vec2(0.0f) };
    };

    // vertex buffer data
    template<typename Vertex>
    struct MeshData
    {
        std::vector<uint32_t> Indices;
        std::vector<Vertex> Vertices;
    };
}
