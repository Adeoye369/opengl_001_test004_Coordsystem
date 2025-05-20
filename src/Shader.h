#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;

struct ShaderSources {
    string vertexSource;
    string fragmentSource;
};

enum shaderType { VERT, FRAG };

class Shader
{
    ShaderSources ParseShaderCode(const string& path) {
        std::ifstream shaderCode(path);
        std::stringstream ss[2];
        int type = -1;
        string line{};

        while (std::getline(shaderCode, line)) {
            if (line.find("#vertex") != std::string::npos) type = VERT;
            else if (line.find("#fragment") != std::string::npos) type = FRAG;
            else ss[(int)type] << line << "\n";
        }


        return { ss[0].str(), ss[1].str() };

    } // End ParseShaderCode

    unsigned int CompileShader(unsigned int type, string& shaderSrc) {

        unsigned int shaderID = glCreateShader(type);

        const char* shaderCode = shaderSrc.c_str();
        glShaderSource(shaderID, 1, &shaderCode, NULL);

        glCompileShader(shaderID);

        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success) {
            int length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
            char* msg = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(shaderID, length, &length, msg);

            std::cout << ((type == GL_VERTEX_SHADER) ? "vertex " : "fragment ") << "shader error :\n" << msg << std::endl;
            glDeleteShader(shaderID);
            return -1;
        }

        return shaderID;
    }


public:
    unsigned int programID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader() {}

    Shader(const char* ShaderPath, const char* geometryPath = nullptr)
    {

        ShaderSources shaderSources = ParseShaderCode(ShaderPath);
        // 1. retrieve the vertex/fragment source code from filePath
        std::string geometryCode;
        std::ifstream gShaderFile;

        // convert stream into string
        string vertexCode = shaderSources.vertexSource;
        string fragmentCode = shaderSources.fragmentSource;


        // if geometry shader path is present, also load a geometry shader
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }

        // 2. compile shaders
        unsigned int vertex, fragment;
        vertex = CompileShader(GL_VERTEX_SHADER, vertexCode);
        fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if (geometryPath != nullptr)
        {
            const char* gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        programID = glCreateProgram();
        glAttachShader(programID, vertex);
        glAttachShader(programID, fragment);
        if (geometryPath != nullptr) glAttachShader(programID, geometry);

        glLinkProgram(programID);
        glValidateProgram(programID);

        checkCompileErrors(programID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != nullptr) glDeleteShader(geometry);

    }
    // activate the shader
    // ------------------------------------------------------------------------

    Shader& operator () (const char* ShaderPath) {
        return *this;
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void useProgram()
    {
        glUseProgram(programID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const{
        glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const{
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const{
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const{
        glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const{
        glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const{
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const{
        glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const{
        glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w){
        glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const{
        glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const{
        glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const{
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif
