#include "shader.h"

// // We don't need geometry shader in this project for now
// Shader::Shader(const char* vertexPath, const char* geometryPath, const char* fragmentPath){
//     // 1. retrieve the vertex/fragment source code from filePath
//     std::string vertexCode;
//     std::string geometryCode;
//     std::string fragmentCode;
//     std::ifstream vShaderFile;
//     std::ifstream gShaderFile;
//     std::ifstream fShaderFile;

//     // ensure ifstream objects can throw exceptions:
//     vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//     gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//     fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//     try
//     {
//         // open files
//         vShaderFile.open(vertexPath);
//         gShaderFile.open(geometryPath);
//         fShaderFile.open(fragmentPath);
//         std::stringstream vShaderStream, gShaderStream, fShaderStream;
//         // read file’s buffer contents into streams
//         vShaderStream << vShaderFile.rdbuf();
//         gShaderStream << gShaderFile.rdbuf();
//         fShaderStream << fShaderFile.rdbuf();
//         // close file handlers
//         vShaderFile.close();
//         gShaderFile.close();
//         fShaderFile.close();
//         // convert stream into string
//         vertexCode = vShaderStream.str();
//         geometryCode = gShaderStream.str();
//         fragmentCode = fShaderStream.str();
//     }
//     catch(std::ifstream::failure e)
//     {
//         std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//     }
//     const char* vShaderCode = vertexCode.c_str();
//     const char* gShaderCode = geometryCode.c_str();
//     const char* fShaderCode = fragmentCode.c_str();
    
//     unsigned int vertex, geometry, fragment;
//     int success;
//     char infoLog[512];
    
//     // vertex Shader
//     vertex = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertex, 1, &vShaderCode, NULL);
//     glCompileShader(vertex);
    
//     // print compile errors if any
//     glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
//     if(!success)
//     {
//         glGetShaderInfoLog(vertex, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
//         infoLog << std::endl;
//     };

//     // Geometry Shader

//     geometry = glCreateShader(GL_GEOMETRY_SHADER);
//     glShaderSource(geometry, 1, &gShaderCode,NULL);
//     glCompileShader(geometry);

//     // print compile errors if any
//     glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
//     if(!success)
//     {
//         glGetShaderInfoLog(geometry, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" <<
//         infoLog << std::endl;
//     };

//     // Fragment Shader

//     fragment = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragment, 1, &fShaderCode,NULL);
//     glCompileShader(fragment);

//     // print compile errors if any
//     glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
//     if(!success)
//     {
//         glGetShaderInfoLog(fragment, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
//         infoLog << std::endl;
//     };

//     ID = glCreateProgram();
//     glAttachShader(ID, vertex);
//     glAttachShader(ID, geometry);
//     glAttachShader(ID, fragment);
//     glLinkProgram(ID);
//     // print linking errors if any
//     glGetProgramiv(ID, GL_LINK_STATUS, &success);
//     if(!success)
//     {
//         glGetProgramInfoLog(ID, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
//         infoLog << std::endl;
//     }
//     // delete shaders; they’re linked into our program and no longer necessary
//     glDeleteShader(vertex);
//     glDeleteShader(geometry);
//     glDeleteShader(fragment);
// }

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;  
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    };

    // Fragment Shader

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode,NULL);
    glCompileShader(fragment);

    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    };

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
        infoLog << std::endl;
    }
    // delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(ID);
}

// Uniform setter functions

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setMat4f(const std::string &name, const float * value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1, GL_FALSE, value);
}
void Shader::setVec3(const std::string &name, const float * value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()),1, value);
}

void Shader::setVec2(const std::string &name, const float * value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()),1, value);
}
