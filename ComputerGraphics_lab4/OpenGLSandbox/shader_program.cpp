#include "shader_program.h"

Shader_program::Shader_program(const char* vertex_path, const char* fragment_path)
{
    string vertex_code;
    string fragment_code;

    ifstream vertex_file;
    ifstream fragment_file;
    vertex_file.exceptions(ifstream::failbit | ifstream::badbit);
    fragment_file.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        vertex_file.open(vertex_path);
        fragment_file.open(fragment_path);

        stringstream vertex_stream;
        stringstream fragment_stream;
        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();

        vertex_file.close();
        fragment_file.close();

        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();
    }
    catch (ifstream::failure)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const char* vertex_char_arr = vertex_code.c_str();
    const char* fragment_char_arr = fragment_code.c_str();

    // vertex shader
    const GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_char_arr, nullptr);
    glCompileShader(vertex);
    check_compile_errors(vertex, type::shader);

    // fragment shader
    const GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_char_arr, nullptr);
    glCompileShader(fragment);
    check_compile_errors(fragment, type::shader);

    // shader program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    check_compile_errors(id, type::program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}



void Shader_program::check_compile_errors(const unsigned int shader, const type _type)
{
    int success;
    char info_log[1024];
    if (_type == type::shader)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, info_log);
            cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << _type << "\n" << info_log <<
                "\n -- --------------------------------------------------- -- " << endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, info_log);
            cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << _type << "\n" << info_log <<
                "\n -- --------------------------------------------------- -- " << endl;
        }
    }
}
