#include <glew.h>
#include "loadShader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    //Create the shaders
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    //Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);

    if (vertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    //Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);

    if (fragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    //Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    //Check Vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
    }

    //Compile Fragment Shader
    printf("Compiling Shader : %s\n", fragment_file_path);
    char const* fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    //Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        printf("%s\n", &fragmentShaderErrorMessage[0]);
    }

    //Link the program
    printf("Linking program\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    //Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}