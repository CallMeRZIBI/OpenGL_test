#include "headerFiles/Model.h"

using namespace std;

const int width = 800;
const int height = 800;

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL is being used
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // Tell GLFW CORE profile is being used
    // So that means only modern functions are present
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "Tutorial"
    GLFWwindow *window = glfwCreateWindow(width, height, "Tutorial", NULL, NULL);
    // Error check if the window fails to create
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the Window
    glViewport(0,0,width,height);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("ResourceFiles/shaders/default.vert", "ResourceFiles/shaders/default.frag");

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Enables depth buffer
    glEnable(GL_DEPTH_TEST);

    // Initializing camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    Model model("models/map/scene.gltf");

    // Main while loop
    while(!glfwWindowShouldClose(window)){
        // Specify the color of the background
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handling camera inputs
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        model.Draw(shaderProgram, camera);

        // Swap the back buffer with the fron buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects
    shaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
