
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

GLFWwindow *g_window;

GLuint g_shaderProgram;
GLint g_progection;
GLint g_madel;
GLint g_MV;
const GLint N = 100;
GLint g_uM;
float W = 800;

class Model
{
public:
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
    GLsizei indexCount;
};

Model g_model;

GLuint createShader(const string code, GLenum type)
{
    GLuint result = glCreateShader(type);
    const GLchar* glCode = code.c_str();
    glShaderSource(result, 1, &glCode, NULL);
    glCompileShader(result);

    GLint compiled;
    glGetShaderiv(result, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(result, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0)
        {
            char infoLog[infoLen];
            glGetShaderInfoLog(result, infoLen, NULL, infoLog);
            cout << "Shader compilation error" << endl << infoLog << endl;
        }
        glDeleteShader(result);
        return 0;
    }

    return result;
}

GLuint createProgram(GLuint vsh, GLuint fsh)
{
    GLuint result = glCreateProgram();

    glAttachShader(result, vsh);
    glAttachShader(result, fsh);

    glLinkProgram(result);

    GLint linked;
    glGetProgramiv(result, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(result, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0)
        {
            char infoLog[infoLen];
            glGetProgramInfoLog(result, infoLen, NULL, infoLog);
            cout << "Shader program linking error" << endl << infoLog << endl;
        }
        glDeleteProgram(result);
        return 0;
    }

    return result;
}

bool createShaderProgram()
{
    g_shaderProgram = 0;

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vShaderFile.open("C:\\Users\\User\\Desktop\\Qt\\MakeLab2\\Shader\\vShader.gl");
        fShaderFile.open("C:\\Users\\User\\Desktop\\Qt\\MakeLab2\\Shader\\fShader.gl");
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        // Считываем данные в потоки
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();
        // Преобразовываем потоки в массив GLchar
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    GLuint vertexShader, fragmentShader;
    vertexShader = createShader(vertexCode, GL_VERTEX_SHADER);
    fragmentShader = createShader(fragmentCode, GL_FRAGMENT_SHADER);

    g_shaderProgram = createProgram(vertexShader, fragmentShader);

    g_progection = glGetUniformLocation(g_shaderProgram, "u_progection");
    g_MV = glGetUniformLocation(g_shaderProgram, "u_MV");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return g_shaderProgram != 0;
}

bool createModel()
{

    GLfloat* vertices = new GLfloat[N*N*2];
    float shiftX = -N/2, shiftZ = -N/2;
    for(GLint x = 0; x < N; x++)
        for(GLint z = 0; z < N; z++)
        {
            vertices[(x*N*2)+(z*2)] = (GLfloat)(x+shiftX);
            vertices[(x*N*2)+(z*2)+1] = (GLfloat)(z+shiftZ);

            //vertices[(x*N*5)+(z*5)+2] = -(x+shiftX)/(2 * pow(abs((x+shiftX)),(3/2.)));
            //vertices[(x*N*5)+(z*5)+3] = 1.0f;
            //vertices[(x*N*5)+(z*5)+4] = -(z+shiftZ)/(2 * pow(abs((z+shiftZ)),(3/2.)));
            //-0.4*exp(-pow( (x-4)*(x-4) + (z-4)*(z-4),2))*(x-4)*((x-4)*(x-4) + (z-4)*(z-4)) - 1/250*exp(-(pow((x-4)*(x-4) + (z-4)*(z-4),2)/1000))*(-4 + x)*((x-4)*(x-4) + (z-4)*(z-4))-0.4*E^(-pow((x+4)*(x+4) + (4+z)*(4+z),2))*(4+x)*((4+x)*(4+x) + (4+z)*(4+z))-1/250*exp(-(pow((4+x)*(4+x) + (4+z)*(4+z),2)/1000))*(4+x)*((4+x)*(4+x) + (4 + z)*(4+z));
        }

    GLuint* indices = new GLuint[(N-1)*(N-1)*6];

    for(int i = 0; i < (N-1); i++)
        for(int j = 0; j < (N-1); j++)
        {
            indices[(i*(N-1)*6)+(j*6)] = N * i + j;
            indices[(i*(N-1)*6)+(j*6)+1] = N * i + 1 + j;
            indices[(i*(N-1)*6)+(j*6)+2] = N * (i+1) + 1 + j;
            indices[(i*(N-1)*6)+(j*6)+3] = N * i + j;
            indices[(i*(N-1)*6)+(j*6)+4] = N * (i+1) + j;
            indices[(i*(N-1)*6)+(j*6)+5] = N * (i+1) + 1 + j;
        }

    /*for(int i=0;i<N*N;i++)
    {
        cout << "(" << vertices[i*5] << ", " << vertices[i*5+1] <<endl;// ")  (" << vertices[i*5+2] << ", " << vertices[i*5+3] << ", " << vertices[i*5+4] << ")" << endl;
    }*/

    glGenBuffers(1, &g_model.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_model.vbo);
    glBufferData(GL_ARRAY_BUFFER, N*N*2 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &g_model.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_model.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (N-1)*(N-1)*6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    g_model.indexCount = (N-1)*(N-1)*6;

    glGenVertexArrays(1, &g_model.vao);
    glBindVertexArray(g_model.vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const GLvoid *)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid *)(2 * sizeof(GLfloat)));

    return g_model.vbo != 0 && g_model.ibo != 0 && g_model.vao != 0;
}

bool init()
{
    // Set initial color of color buffer to white.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    return createShaderProgram() && createModel();
}

void reshape(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void draw()
{
    // Clear color buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(g_shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, g_model.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_model.ibo);
    glBindVertexArray(g_model.vao);
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)800.0f / (GLfloat)600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), glm::vec3( 1.0f,  0.0f,  0.0f));
    view = glm::translate(view, glm::vec3(0.0f,-2.0f,-10.0f));
    view = glm::scale(view,glm::vec3(10.0/N));
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), glm::vec3( 1.0f,  0.0f,  0.0f));
    view = view * rot;
    view = glm::rotate(view,(GLfloat)glfwGetTime(), glm::vec3( 0.0f,  1.0f,  0.0f));

    glUniformMatrix4fv(g_progection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(g_MV, 1, GL_FALSE, glm::value_ptr(view));
    glDrawElements(GL_TRIANGLES, g_model.indexCount, GL_UNSIGNED_INT, NULL);
}

void cleanup()
{
    if (g_shaderProgram != 0)
        glDeleteProgram(g_shaderProgram);
    if (g_model.vbo != 0)
        glDeleteBuffers(1, &g_model.vbo);
    if (g_model.ibo != 0)
        glDeleteBuffers(1, &g_model.ibo);
    if (g_model.vao != 0)
        glDeleteVertexArrays(1, &g_model.vao);
}

bool initOpenGL()
{
    // Initialize GLFW functions.
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return false;
    }

    // Request OpenGL 3.3 without obsoleted functions.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window.
    g_window = glfwCreateWindow(800, 600, "OpenGL Test", NULL, NULL);
    if (g_window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return false;
    }

    // Initialize OpenGL context with.
    glfwMakeContextCurrent(g_window);

    // Set internal GLEW variable to activate OpenGL core profile.
    glewExperimental = true;

    // Initialize GLEW functions.
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return false;
    }

    // Ensure we can capture the escape key being pressed.
    glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set callback for framebuffer resizing event.
    glfwSetFramebufferSizeCallback(g_window, reshape);

    return true;
}

void tearDownOpenGL()
{
    // Terminate GLFW.
    glfwTerminate();
}

int main()
{
    // Initialize OpenGL
    if (!initOpenGL())
        return -1;

    // Initialize graphical resources.
    bool isOk = init();

    if (isOk)
    {
        // Main loop until window closed or escape pressed.
        while (glfwGetKey(g_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(g_window) == 0)
        {
            // Draw scene.
            draw();

            // Swap buffers.
            glfwSwapBuffers(g_window);
            // Poll window events.
            glfwPollEvents();
        }
    }

    // Cleanup graphical resources.
    cleanup();

    // Tear down OpenGL.
    tearDownOpenGL();

    return isOk ? 0 : -1;
}
