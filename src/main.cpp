#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <corecrt_math_defines.h>
#include <functional>

#include "utils/FileLoader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Type alias for a function f(x)
using Function = std::function<float(float)>;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Generate vertex data for a given function
std::vector<float> generateVertices(Function func, int resolution, float xMin, float xMax)
{
    std::vector<float> vertices;
    for (int i = 0; i < resolution; ++i)
    {
        float x = xMin + (xMax - xMin) * i / (resolution - 1);
        float y = func(x);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f); // z-coordinate
    }
    return vertices;
}

int main()
{

    // Define the function to visualize
    Function myFunction = [](float x)
    {
        return x; // Try changing this!
    };

    // Generate vertex data
    int resolution = 1000;
    std::vector<float> vertices = generateVertices(myFunction, resolution, -1.0f, 1.0f);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Moving Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // Load shaders
    // TODO: In linux paths start with ../ instead of ./
    const std::string vertexShaderSource = utils::FileLoader::LoadTextFile("./shaders/vert.glsl");
    const std::string fragmentShaderSource = utils::FileLoader::LoadTextFile("./shaders/frag.glsl");

    const char *vShaderCode = vertexShaderSource.c_str();
    const char *fShaderCode = fragmentShaderSource.c_str();

    //  Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex Shader Compilation Failed:\n"
                  << infoLog << std::endl;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment Shader Compilation Failed:\n"
                  << infoLog << std::endl;
    }

    // Create program
    unsigned int shaderProgram = glCreateProgram();

    // Attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link program
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader Linking Failed:\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glm::vec2 position(0.0f, 0.0f);

    /*
    VBO = the data (your triangle’s vertices)

    VAO = the configuration (how to interpret that data)

    Shader = the logic (what to do with the data)
    */

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, resolution);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
