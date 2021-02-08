#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer
{
public:
	Renderer(const std::string& title, const uint32_t width, const uint32_t height);

	bool isRunning() const;
	void clear() const;
	void draw(
		const VertexArray& vertexArray,
		const IndexBuffer& indexBuffer
	) const;

	inline glm::mat4 getMVPMatrix(const glm::vec3 modelTranslation, const glm::vec3 viewTranslation) const {
		glm::mat4 view = glm::translate(glm::mat4(1.0f), viewTranslation);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslation);

		return projection * view * model; 
	}

private:
	GLFWwindow* m_window;
	glm::mat4 projection;
};