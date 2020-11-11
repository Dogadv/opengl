#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgram
{
    std::string VertexShader;
    std::string FragmentShader;
};

static ShaderProgram ParseShader(const std::string& filepath)
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
            s_stream[(int) currentShaderType] << line << "\n";
        }
    }

    stream.close();

    return { s_stream[(int) ShaderType::VERTEX].str(), s_stream[(int) ShaderType::FRAGMENT].str() };
}

static uint32_t CompileShader(uint32_t type, const std::string& source)
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
        
        char* errorMessage = (char*) _malloca(length * sizeof(char));
        glGetShaderInfoLog(shaderId,length, &length, errorMessage);

        std::cout << "Could not compile a shader!" << "\n" << errorMessage << std::endl;

        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

static uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    uint32_t program = glCreateProgram();
    uint32_t vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return program;
}

static void IncrementColorValue(float_t &increment, float_t &color)
{
    if (color > 1.0f || color < 0.0f)
        increment *= -1;

    color += increment;
}

void GLAPIENTRY OnGLError(GLenum source,
             GLenum type,
             GLuint id,
             GLenum severity,
             GLsizei length,
             const GLchar* message,
             const void* userParam)
{
    std::cout << "type: " << type << ";message: " << message << std::endl;
    //__debugbreak();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OnGLError, 0);

    std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << std::endl;

    const uint32_t TRIANGLE_VERTEX_COUNT = 4;
    const uint32_t VERTEX_COMPONENT_COUNT = 2;
    float positions[TRIANGLE_VERTEX_COUNT * VERTEX_COMPONENT_COUNT] = {
        -.5f, -.5f,
         .5f,  -.5f,
         .5f,  .5f,
        -.5f,  .5f
    };

    const uint32_t VBO_SIZE = sizeof(positions);
    uint32_t vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, VBO_SIZE, positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, VERTEX_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_COMPONENT_COUNT, 0);

    const uint32_t INDECIES_COUNT = 6;
    uint32_t indecies[INDECIES_COUNT] = {
       0, 1, 2,
       2, 3, 0
    };

    const uint32_t IBO_SIZE = sizeof(indecies);
    uint32_t ibo;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBO_SIZE, indecies, GL_STATIC_DRAW);

    ShaderProgram shaderProgram = ParseShader("res/shaders/Basic.shader");
    uint32_t shader = CreateShader(shaderProgram.VertexShader, shaderProgram.FragmentShader);

    glUseProgram(shader);

    float_t r = 0.0f;
    float_t g = 0.3f;
    float_t b = 0.9f;
    float_t i_r = 0.003f;
    float_t i_g = 0.003f;
    float_t i_b = 0.003f;

    int32_t uniformLocation = glGetUniformLocation(shader, "u_Color");
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        IncrementColorValue(i_r, r);
        IncrementColorValue(i_g, g);
        IncrementColorValue(i_b, b);

        glUniform4f(uniformLocation, r, g, b, 1.0f);

        glDrawElements(GL_TRIANGLES, INDECIES_COUNT, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}