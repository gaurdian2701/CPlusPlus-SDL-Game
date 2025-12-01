#include "Assets/GameObjects/TestGameObject.h"
#include "Assets/Components/Renderer2D.h"

void Assets::GameObjects::TestGameObject::Start()
{
	AddComponent<Components::Transform>();
	AddComponent<Components::Renderer2D>();
	GetComponent<Components::Renderer2D>().Color = glm::vec4(0, 0, 255, 255);
}

void Assets::GameObjects::TestGameObject::Update(const float deltaTime)
{
	auto& t = GetComponent<Components::Transform>();
	t.PositionVector.x += m_moveSpeed * deltaTime;
	t.PositionVector.y += m_moveSpeed * deltaTime;
}

