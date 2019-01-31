#version 330 core

in vec3 vertex;
in vec3 color; //variable de entrada de color (recordamos la asignacion con VBOColor)
out vec3 fcolor; //variable de salida de color para el fragment shader.

void main()  {
    fcolor = color; //pasamos el color al fragment
    gl_Position = vec4 (vertex, 1.0);
}
