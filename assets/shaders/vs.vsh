in vec4 a_position;
in vec4 a_color;
in vec2 a_uv1;
out vec4 v_color;
out vec4 v_position;
out vec2 v_uv1;
void main(){
    gl_Position = a_position; 
    v_color = a_color;
    v_position = a_position;
    v_uv1 = a_uv1;
}