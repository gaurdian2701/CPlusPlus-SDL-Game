#include "Core/ECS/Systems/RenderingSystem.h"
#include "Core/ECS/ECSManager.h"
#include "Assets/Components/Transform.h"

void Core::ECS::Systems::RenderingSystem::BeginSystem()
{
}

void Core::ECS::Systems::RenderingSystem::UpdateSystem()
{
	auto& entities = ECSManager::GetInstance()->GetSmallestEntityArray<Assets::Components::Transform>();

	for (auto& entity : entities)
	{
		auto& [transformComponentArray] = m_interestedComponents;
		transformComponentArray[entity].PositionVector.x = 1;
	}
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{

}

