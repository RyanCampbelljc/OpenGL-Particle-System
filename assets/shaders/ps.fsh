
out vec4 PixelColor;
in vec4 v_color;
in vec4 v_position;
#define multiplier 1
void main(){
    // if(int(v_position.y*multiplier) % 2 == (int(v_position.x*multiplier) % 2))//&& (int(v_position.z*multiplier) % 2) == (int(v_position.y*multiplier) % 2))
    //     discard;
    // float alpha = float(int(v_position.x*multiplier) % 2 == (int(v_position.z*multiplier) % 2)&& (int(v_position.z*multiplier) % 2) == (int(v_position.y*multiplier) % 2));
    // vec4 c = vec4(v_color.x,v_color.y,v_color.z,alpha);
    PixelColor = v_color;
}