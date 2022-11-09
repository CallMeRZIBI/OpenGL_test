#include "headerFiles/Texture.h"

Texture::Texture(const char* image, const char* tex_type, GLuint slot, GLenum format, GLenum pixelType){
    // Assigns the type of the texture to the texture object
    type = tex_type;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stor it in byte array
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates and OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, ID);

    // Configures the type of algorithm that is used to minimize and magnify the image
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats itself
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);  // RGBA for jpg and RGB for png ?
    // Generate MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Deletes the image data as it is already in the texture object
    stbi_image_free(bytes);
    // Unbinds the texture object so it cannot be accidentally modified
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit){
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind(){
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}
