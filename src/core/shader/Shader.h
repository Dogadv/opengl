#pragma once

#include <string>
#include <unordered_map>

#include <GL/glew.h>

#include "glm/glm.hpp"

struct ShaderProgram
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void setUniform1i(const std::string& name, GLuint value);
	void setUniform1iv(const std::string& name, GLint value[]);
	void setUniformMat4f(const std::string& name, glm::mat4 value);

private:
	uint32_t m_rendererId;
	std::unordered_map<std::string, int32_t> m_uniformLocationCache;

	uint32_t compileShader(uint32_t type, const std::string& source);
	ShaderProgram parseShader(const std::string& filepath);
	uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int32_t getUniformLocation(const std::string& name);
};