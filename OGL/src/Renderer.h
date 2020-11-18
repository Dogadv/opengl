#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "buffer/vertex/VertexArray.h"
#include "buffer/index/IndexBuffer.h"

class Renderer
{
public:
	Renderer(const std::string& title, const uint32_t width, const uint32_t height);

	bool isRunning() const;
	void clear() const;
	void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer) const;

private:
	GLFWwindow* m_window;
};