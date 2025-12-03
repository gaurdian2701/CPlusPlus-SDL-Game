#include "Assets/GameObjects/TestGameObject.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/CoreSystemsHolder.h"

void Assets::GameObjects::TestGameObject::Start()
{
	AddComponent<Components::Transform>();
	AddComponent<Components::Renderer2D>();

	auto& renderer = GetComponent<Components::Renderer2D>();
	renderer.Initialize(3, SDL_FColor{ 0, 0, 255, 255 });
	renderer.vertexDataArray[0].position.x = 100;
	renderer.vertexDataArray[0].position.y = 0;
	renderer.vertexDataArray[1].position.x = 50;
	renderer.vertexDataArray[1].position.y = 60;
	renderer.vertexDataArray[2].position.x = 150;
	renderer.vertexDataArray[2].position.y = 60;
}

void Assets::GameObjects::TestGameObject::Update(const float deltaTime)
{
	auto& t = GetComponent<Components::Transform>();
	EvaluateMovementInput();

	t.PositionVector.x += m_movementVector.x * m_moveSpeed * deltaTime;
	t.PositionVector.y += m_movementVector.y * m_moveSpeed * deltaTime;
}

void Assets::GameObjects::TestGameObject::EvaluateMovementInput()
{
	m_movementVector.x = 0;
	m_movementVector.y = 0;
	m_rotationValue = 0.0f;

	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_D))
	{
		m_movementVector.x = 1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_A))
	{
		m_movementVector.x = -1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_W))
	{
		m_movementVector.y = -1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_S))
	{
		m_movementVector.y = 1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_LEFT))
	{
		m_rotationValue = -1.0f;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_RIGHT))
	{
		m_rotationValue = 1.0f;
	}
}


