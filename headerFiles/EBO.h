#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "../include/glad/glad.h"
#include <vector>

class EBO{
    public:
        // ID reference of Element Buffer Object
        GLuint ID;
        // Constructor that generates a Element Buffer Object and links it to indicies
        EBO(std::vector<GLuint>& indices);

        // Bidns EBO
        void Bind();
        // Unbinds EBO
        void Unbind();
        // Deletes EBO
        void Delete();
};

#endif
