#pragma once
#include <vector>
#include <memory>
#include <concepts>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"


namespace Core
{
	class Layer;
}

class Renderer;
class Window;

extern void BeginApplication();
extern void UpdateApplication(const float deltaTime);
extern void EndApplication();

class Application
{
public:
	Application();
	virtual ~Application();
	Application(const Application& other) = delete;

	static Application* GetInstance();

	void Init();
	void Run();

	std::vector<std::unique_ptr<Core::Layer>>& GetLayerList();
	SDL_Window* GetMainWindow() const;
	SDL_Renderer* GetMainRenderer() const;

	template<std::derived_from<Core::Layer> T, typename ... LayerArguments>
	void PushLayer(LayerArguments&& ... layerArguments)
	{
		m_layerList.push_back(std::make_unique<T>(std::forward<LayerArguments>(layerArguments) ...));
	}

	void SetBackgroundColor(const SDL_Color someColor)
	{
		m_backgroundColor = someColor;
	}

private:
	void PushLayers();
	void AttachAllLayers() const;
	void UpdateLayerList();
	void DetachAllLayers();
	void InitiateShutdown();
	void RefreshBackground();
	void CheckForQuitEvent();

protected:
	SDL_Window* m_mainWindow = nullptr;
	SDL_Renderer* m_mainRenderer = nullptr;

private:
	std::vector<std::unique_ptr<Core::Layer>> m_layerList;
	SDL_Color m_backgroundColor = { 0, 0, 0, 255 };
	bool m_isRunning = true;
	SDL_Event m_mainEventCatcher;
};

Application& CreateApplication();





