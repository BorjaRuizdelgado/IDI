#version 330 core

out vec4 FragColor;

void main() {
    if(int(gl_FragCoord.y) % 8 > 4) discard; //hay que ir con cuidado ya que hay que castear la cordenada como integer
    else{
    
        if(gl_FragCoord.x > 355){
            FragColor = vec4(1, 0, 0, 1);
        }
        else FragColor = vec4(0,1,0,1);
    }
    
    
}

