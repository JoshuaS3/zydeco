R""(

#version 460 core


in vec3 position;
in vec3 color;
uniform mat4 perspective;

out vec3 vertexColor;


void main()
{
    gl_Position = perspective*vec4(position, 1.0);
    vertexColor = color;
}

)""
