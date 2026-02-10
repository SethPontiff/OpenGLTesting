#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include <glm/glm.hpp>
#include "shaderClass.h"

class Material
{
public:
    glm::vec3 ambient;    
    glm::vec3 diffuse;   
    glm::vec3 specular;   
    float shininess;     

    Material();
    Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shin);
    void SendToShader(Shader& shader);

    static Material Emerald();
    static Material Gold();
    static Material Silver();
    static Material Bronze();
    static Material Ruby();
};

#endif