#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <glm/glm.hpp>
#include "shaderClass.h"

class Light
{
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light();
    Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);

    void SendToShader(Shader& shader, int index);
};

#endif