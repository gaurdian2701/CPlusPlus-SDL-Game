#include "Application/Application.h"

#include <cassert>
#include <chrono>
#include "Core/Layer.h"
#include <iostream>

#include <SDL3/SDL_init.h>
#include "SDL3/SDL_log.h"


Application* MainApplicationInstance = nullptr;
constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 800;

Application::Application()
{
    if (MainApplicationInstance != nullptr)
    {
        std::cout << "Application already exists!" << "\n";
    }
    else
    {
        MainApplicationInstance = this;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL Initialization failed! Error Log: \n %s", SDL_GetError());
    }

    m_mainWindow = SDL_CreateWindow(
        "Asteroids?",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    m_mainRenderer = SDL_CreateRenderer(m_mainWindow, nullptr);

    assert(m_mainWindow != nullptr && "Window Creation Failed!");
}

Application::~Application()
{
    SDL_DestroyRenderer(m_mainRenderer);
    SDL_DestroyWindow(m_mainWindow);
    SDL_Quit();

    m_mainWindow = nullptr;
}

Application* Application::GetInstance()
{
    return MainApplicationInstance;
}

void Application::Init()
{
    PushLayers();
    AttachAllLayers();
}

void Application::PushLayers()
{
    //Push Layers here
}

void Application::AttachAllLayers() const
{
    for (auto& layer : m_layerList)
    {
        layer->OnAttach();
    }
}

void Application::Run()
{
    BeginApplication();
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    SDL_zero(m_mainEventCatcher);

    while (m_isRunning)
    {
        CheckForQuitEvent();

        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        RefreshBackground();

        UpdateApplication(deltaTime.count());
        UpdateLayerList();

        SDL_RenderPresent(m_mainRenderer);
    }

    EndApplication();
    InitiateShutdown();
}

void Application::CheckForQuitEvent()
{
    while (SDL_PollEvent(&m_mainEventCatcher))
    {
        if (m_mainEventCatcher.type == SDL_EVENT_QUIT)
        {
            m_isRunning = false;
        }
    }
}

void Application::RefreshBackground()
{
    SDL_SetRenderDrawColor(m_mainRenderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    SDL_RenderClear(m_mainRenderer);
}

void Application::UpdateLayerList()
{
    for (auto& layer : m_layerList)
    {
        layer->Update();
        layer->Render();
        layer->ProcessInput();
    }
}

std::vector<std::unique_ptr<Core::Layer>>& Application::GetLayerList()
{
    return m_layerList;
}

SDL_Window* Application::GetMainWindow() const
{
    return m_mainWindow;
}

SDL_Renderer* Application::GetMainRenderer() const
{
    return m_mainRenderer;
}

void Application::DetachAllLayers()
{
    for (uint8_t i = 0; i < m_layerList.size(); i++)
    {
        if (m_layerList[i] != nullptr)
        {
            m_layerList[i]->OnDetach();
        }
    }
}

void Application::InitiateShutdown()
{
    DetachAllLayers();
}
