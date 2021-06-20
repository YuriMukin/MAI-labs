#include "Shader.h"


Shader::Shader(const char* VertPath, const char* FigPath)
{
    GLenum err = glewInit();//инициализируем glew
    std::string VertexCode;
    std::string FigureCode;
    std::ifstream VertexCodeF;
    std::ifstream FigureCodeF;
    VertexCodeF.exceptions(std::ifstream::badbit); //считываем код шейлеров 
    FigureCodeF.exceptions(std::ifstream::badbit);
    try
    {
        VertexCodeF.open(VertPath);
        FigureCodeF.open(FigPath);
        std::stringstream VertexCodeStream, FigureCodeStream;
        VertexCodeStream << VertexCodeF.rdbuf();
        FigureCodeStream << FigureCodeF.rdbuf();
        VertexCodeF.close();
        FigureCodeF.close();
        VertexCode = VertexCodeStream.str();
        FigureCode = FigureCodeStream.str();
    }
    catch (std::ifstream::failure e)//проверяем упешность считывания 
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = VertexCode.c_str();
    const GLchar* fShaderCode = FigureCode.c_str();
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);//компилируем шейдер и проверяем все ли прошло хорошо 
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);//записываем шейдеры в в переменную
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::Use()
{
    glUseProgram(Shader::Program); // используем полученый шейдер 
}