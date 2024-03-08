
out vec4 PixelColor;
in vec4 v_color;
in vec4 v_position;
#define multiplier 100
void main(){
    if(int(v_position.x*multiplier) % 2 == (int(v_position.z*multiplier) % 2)&& (int(v_position.z*multiplier) % 2) == (int(v_position.y*multiplier) % 2))
        discard;
    PixelColor = v_color;
}