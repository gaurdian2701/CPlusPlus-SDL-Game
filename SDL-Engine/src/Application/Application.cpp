#include "Application/Application.h"

#include <cassert>
#include <chrono>
#include "Core/Layer.h"
#include <iostream>

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_oldnames.h"

Application* Application::m_applicationInstance = nullptr;
constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 800;

Application::Application()
{
    if (m_applicationInstance != nullptr)
    {
        std::cout << "Application already exists!" << "\n";
    }
    else
    {
        m_applicationInstance = this;
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

    assert(m_mainWindow != nullptr && "Window Creation Failed!");
    m_mainScreenSurface = SDL_GetWindowSurface(m_mainWindow);
}

Application::~Application()
{
    SDL_DestroySurface(m_mainScreenSurface);
    SDL_DestroyWindow(m_mainWindow);
    SDL_Quit();

    m_mainScreenSurface = nullptr;
    m_mainWindow = nullptr;
}

Application* Application::GetInstance()
{
    return m_applicationInstance;
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
    for (auto& layer : LayerList)
    {
        layer->OnAttach();
    }
}

void Application::Run()
{
    BeginApplication();
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (true)
    {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        UpdateApplication(deltaTime.count());

        //Pre Updates here
        SDL_FillSurfaceRect(m_mainScreenSurface, nullptr, SDL_MapSurfaceRGB(m_mainScreenSurface, 5, 78, 1));

        UpdateLayerList();

        //Post Updates here
        SDL_UpdateWindowSurface(m_mainWindow);
    }

    EndApplication();
    InitiateShutdown();
}

void Application::UpdateLayerList()
{
    for (auto& layer : LayerList)
    {
        layer->Update();
        layer->Render();
        layer->ProcessInput();
    }
}

std::vector<std::unique_ptr<Core::Layer>>& Application::GetLayerList()
{
    return LayerList;
}

Window* Application::GetMainWindow()
{
    return nullptr;
}

void Application::DetachAllLayers()
{
    for (uint8_t i = 0; i < LayerList.size(); i++)
    {
        if (LayerList[i] != nullptr)
        {
            LayerList[i]->OnDetach();
        }
    }
}

void Application::CloseGLFWWindow()
{
}

void Application::InitiateShutdown()
{
    DetachAllLayers();
    CloseGLFWWindow();
}
