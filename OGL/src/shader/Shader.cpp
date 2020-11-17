#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram Shader::parseShader(const std::string& filepath)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::stringstream s_stream[2];
    std::string line;

    ShaderType currentShaderType = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                currentShaderType = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                currentShaderType = ShaderType::FRAGMENT;
        }
        else
        {
            s_stream[(int)currentShaderType] << line << "\n";
        }
    }

    stream.close();

    return { s_stream[(int)ShaderType::VERTEX].str(), s_stream[(int)ShaderType::FRAGMENT].str() };
}

static uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    uint32_t program = glCreateProgram();
    uint32_t vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return program;
}

Shader::Shader(const std::string& filepath)
	:m_rendererId(0)
{
}

Shader::~Shader()
{
}

void Shader::bind() const
{
}

void Shader::unbind() const
{
}

void Shader::setUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source)
{
    uint32_t shaderId = glCreateShader(type);
    const char* shaderSource = source.c_str();

    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    int result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char* errorMessage = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(shaderId, length, &length, errorMessage);

        std::cout << "Could not compile a shader!" << "\n" << errorMessage << std::endl;

        glDeleteShader(shaderId);
        return 0;
    }

	return m_rendererId;
}

uint32_t Shader::getUniformLocation(const std::string& name)
{
	return uint32_t();
}
