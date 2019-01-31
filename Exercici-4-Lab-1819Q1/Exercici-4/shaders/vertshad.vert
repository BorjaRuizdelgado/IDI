#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;


out vec3 matamb1;
out vec3 matdiff1;
out vec3 matspec1;
out float matshin1;

out vec3 NormSCO;
out vec3 colFocus1;
out vec3 llumAmbient;
out vec4 posFocusSCO;
out vec4 vertexSCO;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum
vec3 colFocus = vec3(0.8, 0.8, 0.8);
//vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
uniform vec3 posFocus;  //************************************NEEDS CHANGE
uniform float isCamFocus;
//out vec3 fcolor;

vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matamb;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if (dot(NormSCO,L) < 0)
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
    vec3 V = normalize(-vertSCO.xyz);

    if ((dot(R, V) < 0) || (matshin == 0))
      return colRes;  // no hi ha component especular
    
    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), matshin);
    return (colRes + matspec * colFocus * shine); 
}

void main()
{	
    matamb1 = matamb;
	matdiff1 = matdiff;
	matspec1 = matspec;
	matshin1 = matshin;
	
	colFocus1 = colFocus;
	llumAmbient = vec3(0.2, 0.2, 0.2);
	if(isCamFocus == 1.0){
        posFocusSCO = vec4(vec3(0.0,0.0,0.0),1.0); //CAMARA
    }
	else{
        posFocusSCO = view*vec4(posFocus,1.0); 
    }
	vertexSCO = view * TG * vec4 (vertex, 1.0);
	
	NormSCO = inverse(transpose(mat3(view*TG)))*normal;
	NormSCO = normalize(NormSCO);
	
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
