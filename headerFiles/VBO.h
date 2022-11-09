#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "../include/glm/glm.hpp"
#include "../include/glad/glad.h"
#include <vector>

// Structure to standardize the vertices used in the meshes
struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO{
    public:
        // Reference ID of the Vertex Buffer Object
        GLuint ID;
        // Constructor that generates a Vertex Buffer Object and links it ot vertices
        VBO(std::vector <Vertex>& vertices);

        // Binds VBO
        void Bind();
        // Unbinds VBO
        void Unbind();
        // Deletes VBO
        void Delete();
};

#endif
