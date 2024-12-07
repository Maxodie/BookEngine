#pragma once
#include "Graphics/Buffers/Vertex.hpp"
#include <cstddef>

namespace Book
{
    template<typename Vertex>
    struct Mesh
    {
        BOOK_INLINE Mesh(const MeshData<Vertex>& data)
        {
            if(data.Vertices.empty())
            {
                BOOK_CORE_ERROR("Mesh(): empty mesh data");
                return;
            }

            // number of vertices ans indices
            m_NbrVertex = data.Vertices.size();
            m_NbrIndex = data.Indices.size();

            // generate vertex buffer arrzay
            glGenVertexArrays(1, &m_BufferID);

            // active/bind vertex array
            glBindVertexArray(m_BufferID);

            // create vertex buffer
            uint32_t VBO = 0;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, m_NbrVertex * sizeof(Vertex),
                         data.Vertices.data(), GL_STATIC_DRAW);

            // create element buffer
            if(m_NbrIndex != 0)
            {
                uint32_t EBO = 0;
                glGenBuffers(1, &EBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NbrIndex * sizeof(uint32_t),
                            data.Indices.data(), GL_STATIC_DRAW);

            }

            if(TypeID<Vertex>() == TypeID<ShadedVertex>())
            {
                SetAttribute(0, 3, offsetof(ShadedVertex, Position));
                SetAttribute(1, 3, offsetof(ShadedVertex, Normal));
                SetAttribute(2, 2, offsetof(ShadedVertex, UVs));
            }
            else if (TypeID<Vertex>() == TypeID<FlatVertex>())
            {
                SetAttribute(0, 3, offsetof(FlatVertex, Position));
                SetAttribute(1, 4, offsetof(FlatVertex, Color));
            }
            else if (TypeID<Vertex>() == TypeID<QuadVertex>())
            {
                SetAttribute(0, 4, offsetof(QuadVertex, Data));
            }
            else
            {
                BOOK_CORE_ERROR(false && "invalid vertex type");
            }

            // unbind vertex array
            glBindVertexArray(0);
        }

        BOOK_INLINE void Draw(uint32_t mode)
        {
            glBindVertexArray(m_BufferID);
            if(m_NbrIndex != 0)
            {
                glDrawElements(mode, m_NbrIndex, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
                return;
            }
            glDrawArrays(mode, 0, m_NbrVertex);
            glBindVertexArray(0);
        }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &m_BufferID);
    }

    private:
        BOOK_INLINE void SetAttribute(uint32_t index, int32_t size, const void* value)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), value);
        }

    private:
        uint32_t m_NbrVertex = 0;
        uint32_t m_NbrIndex = 0;
        uint32_t m_BufferID = 0;
    };

    using ShadedMesh = Mesh<ShadedVertex>;
    using Mesh3D = std::shared_ptr<ShadedMesh>;
}
