#pragma once
#include "vec3.hpp"

namespace Assets::Components
{
    struct Renderer2D
    {
        //Default Constructor
        Renderer2D() = default;

        template<int ArraySize>
        explicit Renderer2D(glm::vec<4, int>&& someColor)
        {
            Color = someColor;
        }

        //Move Constructor
        Renderer2D(Renderer2D&& other) noexcept
        {
            Color = other.Color;
        }

        //Move Assignment Operator
        Renderer2D& operator=(Renderer2D&& other) noexcept
        {
            if (this != &other)
            {
                Color = other.Color;
            }

            return *this;
        }

        //Copy Constructor
        Renderer2D(const Renderer2D& other)
        {
            Color = other.Color;
        }

        glm::vec<4, int> Color = glm::vec<4, int>(255, 255, 255, 255);
    };
}