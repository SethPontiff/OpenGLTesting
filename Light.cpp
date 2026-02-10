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

void Light::SendToShader(Shader& shader)
{
    shader.Activate();
    glUniform3f(glGetUniformLocation(shader.ID, "light.position"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.ID, "light.ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.ID, "light.diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.ID, "light.specular"), specular.x, specular.y, specular.z);
}