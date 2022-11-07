#include "headerFiles/shaderClass.h"

// Reads a text file and outputs a string with everything from the text file
std::string get_file_contents(const char* filename){
    std::ifstream in(filename, std::ios::binary);
    if(in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile){
    // Read vertex file and fragment file and store the string
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create vertex shader object and get reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source to the vertex shader object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile vertex shader into machine code
    glCompileShader(vertexShader);
    // Check if shader compiled successfully
    compileErrors(vertexShader, "VERTEX");

    // The same as with vertex shader but with fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    // Create shader program object and get its reference
    ID = glCreateProgram();
    // Attach the vertex and fragment shaders to the shader program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shader together into the shader program
    glLinkProgram(ID);
    // Check if Shaders linked successfully
    compileErrors(ID, "PROGRAM");

    // Delete the now useless Vertex and Fragment shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type){
    GLint success = 0;

    if(type != "PROGRAM"){
        // Checking if any errors occured while compilation
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE){
            // Getting the length of error message
            GLint logSize = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

            // Getting info log
            if(logSize > 0){
                char* errorLog = (char*)malloc(logSize);
                GLsizei written;
                glGetShaderInfoLog(shader, logSize, &written, errorLog);

                std::cout << "Error occured while compiling Shader:\n" << errorLog << std::endl;
                free(errorLog);
            }
        }
    }else{
        glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE){
            // Getting the length of error message
            GLint logSize = 0;
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logSize);

            // Getting info log
            if(logSize > 0){
                char* errorLog = (char*)malloc(logSize);
                GLsizei written;
                glGetProgramInfoLog(shader, logSize, &written, errorLog);

                std::cout << "Error occured while linking Shaders:\n" << errorLog << std::endl;
                free(errorLog);
            }
        }
    }
}
