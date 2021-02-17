#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"

#include "../camera/Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer
{
public:
	Renderer(const std::string& title, const uint32_t width, const uint32_t height, Camera& camera);

	bool isRunning() const;
	void clear() const;
	void update() const;

	void draw(
		const VertexArray& vertexArray,
		const IndexBuffer& indexBuffer
	) const;

	void setKeyCallback(GLFWkeyfun callback) const;
	void translateCamera(glm::vec3 cameratranslation);

	inline GLFWwindow* getWindow() const { return m_window; }

	inline glm::mat4 getMVPMatrix(const glm::vec3 modelTranslation, const float zoom) const 
	{
		glm::vec3 cameraPosition = m_camera.getCameraPosition();
		float cameraZoom = m_camera.getZoom();

		glm::mat4 projectionMatrix = m_camera.getProjection();
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), modelTranslation);
		glm::mat4 viewMatrix = glm::scale(glm::translate(glm::mat4(1.0f), cameraPosition), glm::vec3(cameraZoom, cameraZoom, 1));

		return projectionMatrix * viewMatrix * modelMatrix;
	}

private:
	Camera& m_camera;

	GLFWwindow* m_window;
};