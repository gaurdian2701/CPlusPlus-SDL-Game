cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME KMiniEngine)

project(${PROJECT_NAME})

set(ENGINE_BINARY_NAME KMiniEngineLib)
set(VENDOR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include)

add_subdirectory(vendor)

add_library(
        ${ENGINE_BINARY_NAME}
            STATIC
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Application/Application.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/IO/FileSystem/FileHandler.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Events/EventSystem.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/GameScene.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/ECS/ECSManager.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/ECS/Systems/MovementSystem.cpp)

target_include_directories(
        ${ENGINE_BINARY_NAME}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include)

target_link_libraries(
        ${ENGINE_BINARY_NAME}
            PUBLIC
                vendor)

set_target_properties(${ENGINE_BINARY_NAME}
        PROPERTIES
            LINKER_LANGUAGE CXX)
