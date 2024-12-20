#pragma once
#include "Auxiliaries/ECS.hpp"

namespace Book
{
    struct Application : AppInterface
    {
        BOOK_INLINE Application()
        {
            // initialize app comtext
            m_LayerID = TypeID<Application>();
            m_Context = new AppContext();

            // attach window resize event callback
            AttachCallback<WindowResizeEvent>([this] (auto e)
            {
                m_Context->Renderer->Resize(e.Width, e.Height);
            });
        }

        BOOK_INLINE ~Application()
        {
            BOOK_DELETE(m_Context);
        }

        BOOK_INLINE void RunContext()
        {
            // create scene camera
            Entity camera = CreateEntt<Entity>();
            camera.Attach<TransformComponent>().Transform.Translate.z = 2.0f;
            camera.Attach<CameraComponent>();

            // create cube
            Model3D model = std::make_unique<Model>("Resources/Models/cube.fbx");
            Entity cube = CreateEntt<Entity>();
            cube.Attach<TransformComponent>().Transform.Rotation.y = 30.f;
            cube.Attach<ModelComponent>().Model = model;

            Entity cube2 = CreateEntt<Entity>();
            TransformComponent& tr = cube2.Attach<TransformComponent>();
            tr.Transform.Rotation.y = 70.f;
            tr.Transform.Translate.y = 1.f;
            cube2.Attach<ModelComponent>().Model = model;

            while(m_Context->Window->PollEvents())
            {
                // render new frame
                m_Context->Renderer->NewFrame();

                // set shader camera
                EnttView<Entity, CameraComponent>([this] (auto entity, auto& comp)
                {
                    auto& transform { entity.template Get<TransformComponent>().Transform };
                    m_Context->Renderer->SetCamera(comp.Camera, transform);
                });

                // render models
                EnttView<Entity, ModelComponent>([this] (auto entity, auto& comp)
                {
                    auto& transform { entity.template Get<TransformComponent>().Transform };
                    m_Context->Renderer->Draw(comp.Model, transform);
                });

                m_Context->Renderer->EndFrame();

                // update layers
                for(auto& layer : m_Context->Layers)
                {
                    layer->OnUpdate();
                }

                // show frame to screen
                m_Context->Renderer->ShowFrame();
            }
        }
    };
}
