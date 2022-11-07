#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "../include/glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader{
    public:
        // Reference ID of the Shader Program
        GLuint ID;
        // Creates Shader program from Vertex file and Fragment file
        Shader(const char* vertexFile, const char* fragmentFile);

        // Activates Shader Program
        void Activate();
        // Deletes the Shader Program
        void Delete();

    private:
        // Check for compilation errors
        void compileErrors(unsigned int shader, const char* type);
};

#endif
