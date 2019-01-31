#version 330 core

in vec3 vertex;
in vec3 color;

uniform mat4 TG;
uniform mat4 Proj;

out vec3 fcolor;

void main()  {
    fcolor = color;
    gl_Position = Proj * TG * vec4 (vertex, 1.0);
}
