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
#include <QString>
#include <QDir>
#include "model.h"
#include <libjpeg/jpeglib.h>
#include <stdio.h>
#include <setjmp.h>

using namespace std;

GLFWwindow *g_window;

GLuint g_shaderProgram;
GLint g_progection;
GLint g_MV;
const GLint N = 500;
GLint g_uM;
float W = 800;

Model g_model;

bool createModel()
{
    std::array<GLfloat,N*N*4>* vertices= new std::array<GLfloat,N*N*4>();
    float shiftX = -N/2, shiftZ = -N/2;
    for(GLint x = 0; x < N; x++)
        for(GLint z = 0; z < N; z++)
        {
            (*vertices)[(x*N*4)+(z*4)] = (GLfloat)(x+shiftX);
            (*vertices)[(x*N*4)+(z*4)+1] = (GLfloat)(z+shiftZ);
            (*vertices)[(x*N*4)+(z*4)+2] = x/float(N);
            (*vertices)[(x*N*4)+(z*4)+3] = z/float(N);
        }

    std::array<GLuint,(N-1)*(N-1)*6>* indices= new std::array<GLuint,(N-1)*(N-1)*6>();

    for(int i = 0; i < (N-1); i++)
        for(int j = 0; j < (N-1); j++)
        {
            (*indices)[(i*(N-1)*6)+(j*6)] = N * i + j;
            (*indices)[(i*(N-1)*6)+(j*6)+1] = N * i + 1 + j;
            (*indices)[(i*(N-1)*6)+(j*6)+2] = N * (i+1) + 1 + j;
            (*indices)[(i*(N-1)*6)+(j*6)+3] = N * i + j;
            (*indices)[(i*(N-1)*6)+(j*6)+4] = N * (i+1) + j;
            (*indices)[(i*(N-1)*6)+(j*6)+5] = N * (i+1) + 1 + j;
        }
    g_model.setVertices(*vertices,*indices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (const GLvoid *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (const GLvoid *)(2*sizeof(GLfloat)));

    return g_model.vbo != 0 && g_model.ibo != 0 && g_model.vao != 0;
}


struct my_error_mgr {
  struct jpeg_error_mgr pub;

  jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr *my_error_ptr;

void my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

bool createTexture(GLuint& texture, string filename)
{
    struct jpeg_decompress_struct cinfo;

    struct my_error_mgr jerr;
    FILE *infile;
    JSAMPARRAY buffer;
    int row_stride;

    //string filename = "D:/Qt Progects/ComputerGraphics_lab3/rust_texture.jpg";
    if ((infile = fopen(filename.c_str(), "rb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", filename);
        return false;
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return false;
    }
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


    std::vector<JSAMPLE> bitMap;
    GLint width = cinfo.output_width, height = cinfo.output_height;
    while (cinfo.output_scanline < cinfo.output_height)
    {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        //put_scanline_someplace(buffer[0], row_stride);
        for(int i =0;i<row_stride;i++)
        {
            bitMap.push_back(*(buffer[0]+i));
        }
    }

    texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitMap.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return true;
}

bool init()
{
    // Set initial color of color buffer to white.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    g_model.setProgram(":/Shader/vShader.gl",":/Shader/fShader.gl");
    g_progection = glGetUniformLocation(g_model.shaderProgram, "u_progection");
    g_MV = glGetUniformLocation(g_model.shaderProgram, "u_MV");
    return (g_model.shaderProgram!=0) && createModel() && createTexture(g_model.texture1,"D:/Qt Progects/ComputerGraphics_lab3/iron_texture.jpg")
            && createTexture(g_model.texture2,"D:/Qt Progects/ComputerGraphics_lab3/rust_texture.jpg");
}

void reshape(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void draw()
{
    // Clear color buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(g_model.shaderProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_model.texture1);
    glUniform1i(glGetUniformLocation(g_model.shaderProgram, "texture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, g_model.texture2);
    glUniform1i(glGetUniformLocation(g_model.shaderProgram, "texture2"), 1);

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)800.0f / (GLfloat)600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), glm::vec3( 1.0f,  0.0f,  0.0f));
    view = glm::translate(view, glm::vec3(0.0f,-2.0f,-10.0f));
    view = glm::scale(view,glm::vec3(10.0/N));
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(45.0f), glm::vec3( 1.0f,  0.0f,  0.0f));
    view = view * rot;
    view = glm::rotate(view,(GLfloat)glfwGetTime(), glm::vec3( 0.0f,  1.0f,  0.0f));

    glUniformMatrix4fv(g_progection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(g_MV, 1, GL_FALSE, glm::value_ptr(view));
    g_model.Draw();
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
