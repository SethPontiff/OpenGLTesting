#include "Light.h"

Light::Light()
    : position(1.2f, 1.0f, 2.0f),
    ambient(0.2f, 0.2f, 0.2f),
    diffuse(0.5f, 0.5f, 0.5f),
    specular(1.0f, 1.0f, 1.0f)
{
}

Light::Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
    : position(pos), ambient(amb), diffuse(diff), specular(spec)
{ 
}

void Light::SendToShader(Shader& shader, int index)
{
    shader.Activate();
    std::string lightStr = "lights[" + std::to_string(index) + "]";

    glUniform3f(glGetUniformLocation(shader.ID, (lightStr + ".position").c_str()),
        position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.ID, (lightStr + ".ambient").c_str()),
        ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.ID, (lightStr + ".diffuse").c_str()),
        diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.ID, (lightStr + ".specular").c_str()),
        specular.x, specular.y, specular.z);
}
