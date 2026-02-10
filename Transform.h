#pragma once
#ifndef TRANSFORM_CLASS_H
#define TRANSFORM_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform();
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);

    glm::mat4 GetModelMatrix() const;

    void Translate(glm::vec3 offset);
    void Rotate(glm::vec3 eulerAngles);
    void Scale(glm::vec3 scaleFactor);
};

#endif