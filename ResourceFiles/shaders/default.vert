#version 460 core
// Position/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture
layout (location = 3) in vec2 aTex;


// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;



// Imports the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));

    gl_Position = camMatrix * vec4(crntPos, 1.0f);
    // Assigns the aColor to output value
    color = aColor;
    // Assigns the aTex to te texCoord output value
    texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
    Normal = aNormal;
}
