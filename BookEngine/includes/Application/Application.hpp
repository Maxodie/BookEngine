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

            Model3D model = std::make_unique<Model>("Resources/Models/cube.fbx");
            Model3D model2 = std::make_unique<Model>("Resources/Models/sphere.fbx");

            // create sphere
            Entity sphere = CreateEntt<Entity>();
            sphere.Attach<ModelComponent>().Model = model2;
            auto& trSphere = sphere.Attach<TransformComponent>().Transform;
            trSphere.Translate = glm::vec3(1.5f);

            Entity light = CreateEntt<Entity>();
            auto& tr2 = light.Attach<TransformComponent>().Transform;
            light.Attach<PointLightComponent>().Light.Radiance.b = 0.0f;
            tr2.Translate = glm::vec3(-0.5f, 0.0f, 2.0f);

            Entity light2 = CreateEntt<Entity>();
            auto& tr3 = light.Attach<TransformComponent>().Transform;
            light.Attach<PointLightComponent>().Light.Radiance.g = 0.0f;
            tr3.Translate = glm::vec3(0.5f, 0.0f, 2.0f);

            while(m_Context->Window->PollEvents())
            {
                // render new frame
                m_Context->Renderer->NewFrame();

                int32_t lightCounter = 0;

                EnttView<Entity, PointLightComponent>([this, &lightCounter] (auto entity, auto& comp)
                {
                    auto& transform = entity.template Get<TransformComponent>().Transform;
                    m_Context->Renderer->SetPointLight(comp.Light, transform, lightCounter);
                    lightCounter++;
                });

                m_Context->Renderer->SetPointLightCount(lightCounter);

                // set shader camera
                EnttView<Entity, CameraComponent>([this] (auto entity, auto& comp)
                {
                    auto& transform { entity.template Get<TransformComponent>().Transform };
                    m_Context->Renderer->SetCamera(comp.Camera, transform);
                    transform.Rotation.y += 0.1f;
                });

                // render models
                EnttView<Entity, ModelComponent>([this] (auto entity, auto& comp)
                {
                    auto& transform { entity.template Get<TransformComponent>().Transform };
                    m_Context->Renderer->Draw(comp.Model, comp.Material, transform);
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
