#pragma once
#include <iostream>
#include <mat4x4.hpp>
#include "gtc/quaternion.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/quaternion.hpp"
#include "ext/matrix_transform.hpp"

namespace Assets::Components
{
    struct Transform
    {
        //Default Constructor
        Transform()
        {
            std::cout << "Transform default constructor called \n" << std::flush;
        }

        //Move Constructor
        Transform(Transform&& other) noexcept
        {
            std::cout << "Transform move constructor called \n" << std::flush;

            PositionVector = other.PositionVector;
            RotationVector = other.RotationVector;
            ScaleVector = other.ScaleVector;
        }

        //Move Assignment operator
        Transform& operator=(Transform&& other) noexcept
        {
            std::cout << "Transform assignment operator called \n" << std::flush;

            if (this != &other)
            {
                PositionVector = other.PositionVector;
                RotationVector = other.RotationVector;
            }
            return *this;
        }

        //Copy Constructor
        Transform(const Transform& other)
        {
            std::cout << "Transform copy constructor called \n" << std::flush;

            PositionVector = other.PositionVector;
            RotationVector = other.RotationVector;
        }

        glm::mat4 GetModelMatrix()
        {
            glm::mat4 translationMatrix = glm::mat4(1.0f);
            glm::mat4 rotationMatrix = glm::mat4(1.0f);
            glm::mat4 scaleMatrix = glm::mat4(1.0f);

            translationMatrix = glm::translate(translationMatrix, glm::vec3(PositionVector.x, PositionVector.y, PositionVector.z));
            rotationMatrix = glm::toMat4(glm::quat(glm::vec3(RotationVector.x, RotationVector.y, RotationVector.z)));
            scaleMatrix = glm::scale(scaleMatrix, glm::vec3(ScaleVector.x, ScaleVector.y, ScaleVector.z));

            return translationMatrix * rotationMatrix * scaleMatrix;
        }

        glm::vec3 PositionVector = glm::vec3(0.0f);
        glm::vec3 RotationVector = glm::vec3(0.0f);
        glm::vec3 ScaleVector = glm::vec3(1.0f);
    };
}
