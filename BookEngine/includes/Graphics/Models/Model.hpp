#pragma once
#include <assimp/postprocess.h>
#include <assimp/quaternion.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Graphics/Models/Helper.hpp"

namespace Book
{
    struct Model
    {
        BOOK_INLINE Model() = default;

        BOOK_INLINE Model(const std::string& filename)
        {
            Load(filename);
        }

        BOOK_INLINE void Load(const std::string& filename)
        {
            Assimp::Importer importer;
            uint32_t flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                             aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes |
                             aiProcess_OptimizeGraph | aiProcess_ValidateDataStructure |
                             aiProcess_ImproveCacheLocality | aiProcess_FixInfacingNormals |
                             aiProcess_GenUVCoords | aiProcess_FlipUVs;

            const aiScene* ai_scene = importer.ReadFile(filename, flags);

            if(!ai_scene || ai_scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
            {
                BOOK_CORE_ERROR("failed to load model {}", importer.GetErrorString());
                return;
            }

            // parse all meshes
            ParseNode(ai_scene, ai_scene->mRootNode);
        }

        BOOK_INLINE void Draw(uint32_t mode)
        {
            for(auto& mesh : m_Meshes)
            {
                mesh->Draw(mode);
            }
        }

    private:
        BOOK_INLINE void ParseNode(const aiScene* ai_scene, aiNode* ai_node)
        {
            for(uint32_t i = 0; i < ai_node->mNumMeshes; i++)
            {
                ParseMesh(ai_scene->mMeshes[ai_node->mMeshes[i]]);
            }

            for(uint32_t i = 0; i < ai_node->mNumChildren; i++)
            {
                ParseNode(ai_scene, ai_node->mChildren[i]);
            }
        }

        BOOK_INLINE void ParseMesh(aiMesh* ai_mesh)
        {
            MeshData<ShadedVertex> data;
            data.Vertices.reserve(ai_mesh->mNumVertices);

            // vertices
            for(uint32_t i = 0; i < ai_mesh->mNumVertices; i++)
            {
                ShadedVertex vertex;

                // positions
                vertex.Position = AssimpToVec3(ai_mesh->mVertices[i]);

                // normals
                vertex.Normal = AssimpToVec3(ai_mesh->mNormals[i]);

                // texcoords
                vertex.UVs.x = ai_mesh->mTextureCoords[0][i].x;
                vertex.UVs.y = ai_mesh->mTextureCoords[0][i].y;

                data.Vertices.push_back(vertex);
            }

            // indices
            uint32_t j{0};
            for(uint32_t i = 0; i < ai_mesh->mNumFaces; i++)
            {
                for(j = 0; j < ai_mesh->mFaces[i].mNumIndices; j++)
                {
                    data.Indices.push_back(ai_mesh->mFaces[i].mIndices[j]);
                }
            }

            m_Meshes.emplace_back(std::make_unique<ShadedMesh>(data));
        }

    private:
        std::vector<Mesh3D> m_Meshes;
    };

    // 3d model typedef
    using Model3D = std::shared_ptr<Model>;
}
