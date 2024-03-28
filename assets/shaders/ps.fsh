
uniform sampler2D u_texture1;

out vec4 PixelColor;
in vec4 v_color;
in vec4 v_position;
in vec2 v_uv1;

void main(){
    vec4 c = texture(u_texture1, v_uv1) * v_color;
    // if(c.a < 0.1){
    //     discard;
    // }
    PixelColor = c;
}