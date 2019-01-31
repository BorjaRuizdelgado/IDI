#version 330 core

out vec4 FragColor;
in vec3 fcolor;
uniform float scl; 

void main() {
    FragColor = vec4(fcolor*scl, 1); //Asignamos el color al fragmento que habiamos pasado por el vertex.
}

