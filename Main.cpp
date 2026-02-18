#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>
#include<cmath>

#include"shaderClass.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Transform.h"
#include"Material.h"
#include"Light.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void generateDonut(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices,
	float majorRadius, float minorRadius, int majorSegments, int minorSegments)
{
	vertices.clear();
	indices.clear();

	for (int i = 0; i <= majorSegments; i++)
	{
		float theta = 2.0f * M_PI * i / majorSegments;
		float cosTheta = cos(theta);
		float sinTheta = sin(theta);

		for (int j = 0; j <= minorSegments; j++)
		{
			float phi = 2.0f * M_PI * j / minorSegments;
			float cosPhi = cos(phi);
			float sinPhi = sin(phi);

			float x = (majorRadius + minorRadius * cosPhi) * cosTheta;
			float y = (majorRadius + minorRadius * cosPhi) * sinTheta;
			float z = minorRadius * sinPhi;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			float nx = cosPhi * cosTheta;
			float ny = cosPhi * sinTheta;
			float nz = sinPhi;
			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);

			float s = (float)i / majorSegments;
			float t = (float)j / minorSegments;
			vertices.push_back(s);
			vertices.push_back(t);
		}
	}

	for (int i = 0; i < majorSegments; i++)
	{
		for (int j = 0; j < minorSegments; j++)
		{
			int first = i * (minorSegments + 1) + j;
			int second = first + minorSegments + 1;

			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(first + 1);

			indices.push_back(second);
			indices.push_back(second + 1);
			indices.push_back(first + 1);
		}
	}
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLTest", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	generateDonut(vertices, indices, 1.0f, 0.4f, 48, 24);

	Shader shaderProgram("default.vert", "default.frag");

	Texture texture("texturetest.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices.data(), vertices.size() * sizeof(GLfloat));
	EBO EBO1(indices.data(), indices.size() * sizeof(GLuint));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));
	Transform donutTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));

	Material donutMaterial = Material::Gold();

	Light light1(
		glm::vec3(2.0f, 2.0f, 2.0f),   
		glm::vec3(0.1f, 0.1f, 0.1f),   
		glm::vec3(1.0f, 1.0f, 1.0f),  
		glm::vec3(1.0f, 1.0f, 1.0f)     
	);

	Light light2(
		glm::vec3(-2.0f, 1.0f, 2.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f),   
		glm::vec3(1.0f, 0.0f, 0.0f),  
		glm::vec3(1.0f, 0.0f, 0.0f)   
	);

	Light light3(
		glm::vec3(0.0f, -1.0f, 2.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f),  
		glm::vec3(0.0f, 0.0f, 1.0f)   
	);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.UpdateAutoMovement(deltaTime, 5.0f);

		donutTransform.rotation.y += 30.0f * deltaTime;
		donutTransform.rotation.x += 15.0f * deltaTime;

		glm::mat4 model = donutTransform.GetModelMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix(800.0f / 800.0f);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		donutMaterial.SendToShader(shaderProgram);
		light1.SendToShader(shaderProgram, 0);
		light2.SendToShader(shaderProgram, 1);
		light3.SendToShader(shaderProgram, 2);

		glUniform3f(glGetUniformLocation(shaderProgram.ID, "viewPos"),
			camera.position.x, camera.position.y, camera.position.z);

		texture.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	texture.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}