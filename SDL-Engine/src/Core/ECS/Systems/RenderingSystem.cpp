#include "Core/ECS/Systems/RenderingSystem.h"

#include "Application/Application.h"
#include "Core/ECS/ECSManager.h"
#include "Assets/Components/Transform.h"

#include "SDL3/SDL_render.h"

void Core::ECS::Systems::RenderingSystem::BeginSystem()
{
}

void Core::ECS::Systems::RenderingSystem::UpdateSystem()
{
	const auto& entities = ECSManager::GetInstance()->GetSmallestDenseEntityArray<Assets::Components::Transform,
	Assets::Components::Renderer2D>();
	const auto& [denseTransformArray, denseRenderer2DArray] = m_interestedDenseComponentArrays;
	const auto& [sparseTransformArray, sparseRenderer2DArray] = m_interestedSparseArrays;

	for (const auto& entityID : entities)
	{
		Assets::Components::Transform& transform = denseTransformArray[sparseTransformArray[entityID]];
		Assets::Components::Renderer2D& renderer2D = denseRenderer2DArray[sparseRenderer2DArray[entityID]];

		SDL_SetRenderDrawColor(Application::GetInstance()->GetMainRenderer(),
			renderer2D.Color.r, renderer2D.Color.g, renderer2D.Color.b, renderer2D.Color.a);

		SDL_RenderGeometry(Application::GetInstance()->GetMainRenderer(),
			nullptr,
			renderer2D.vertexDataArray,
			renderer2D.vertexDataArraySize,
			nullptr,
			0);
	}
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{

}

