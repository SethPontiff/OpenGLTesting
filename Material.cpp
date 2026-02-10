#include "Material.h"

Material::Material()
    : ambient(0.2f, 0.2f, 0.2f),
    diffuse(0.8f, 0.8f, 0.8f),
    specular(1.0f, 1.0f, 1.0f),
    shininess(32.0f)
{
}

Material::Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shin)
    : ambient(amb), diffuse(diff), specular(spec), shininess(shin)
{
}

void Material::SendToShader(Shader& shader)
{
    shader.Activate();
    glUniform3f(glGetUniformLocation(shader.ID, "material.ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.ID, "material.diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.ID, "material.specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), shininess);
}

Material Material::Emerald()
{
    return Material(
        glm::vec3(0.0215f, 0.1745f, 0.0215f),
        glm::vec3(0.07568f, 0.61424f, 0.07568f),
        glm::vec3(0.633f, 0.727811f, 0.633f),
        76.8f
    );
}

Material Material::Gold()
{
    return Material(
        glm::vec3(0.24725f, 0.1995f, 0.0745f),
        glm::vec3(0.75164f, 0.60648f, 0.22648f),
        glm::vec3(0.628281f, 0.555802f, 0.366065f),
        51.2f
    );
}

Material Material::Silver()
{
    return Material(
        glm::vec3(0.19225f, 0.19225f, 0.19225f),
        glm::vec3(0.50754f, 0.50754f, 0.50754f),
        glm::vec3(0.508273f, 0.508273f, 0.508273f),
        51.2f
    );
}

Material Material::Bronze()
{
    return Material(
        glm::vec3(0.2125f, 0.1275f, 0.054f),
        glm::vec3(0.714f, 0.4284f, 0.18144f),
        glm::vec3(0.393548f, 0.271906f, 0.166721f),
        25.6f
    );
}

Material Material::Ruby()
{
    return Material(
        glm::vec3(0.1745f, 0.01175f, 0.01175f),
        glm::vec3(0.61424f, 0.04136f, 0.04136f),
        glm::vec3(0.727811f, 0.626959f, 0.626959f),
        76.8f
    );
}