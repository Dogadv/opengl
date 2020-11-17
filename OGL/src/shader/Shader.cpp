#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath)
    :m_rendererId(0)
{
    ShaderProgram shaderProgram = parseShader(filepath);
    m_rendererId = createShader(shaderProgram.VertexShader, shaderProgram.FragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_rendererId);
}

void Shader::bind() const
{
    glUseProgram(m_rendererId);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

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

uint32_t Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
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

	return shaderId;
}

int32_t Shader::getUniformLocation(const std::string& name)
{
    int32_t location = glGetUniformLocation(m_rendererId, name.c_str());
    if (location == -1)
        std::cout << "ERROR! uniform: " << name << " was not found in a shader declaratiom" << std::endl;

    return location;
}
