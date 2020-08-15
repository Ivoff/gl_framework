#version 450 core

out vec4 v_color;

void main() {
    const vec4 pos[3] = vec4[3](
        vec4( 0.0,  0.5, 0.5, 1.0),
        vec4( 0.5, -0.5, 0.5, 1.0),
        vec4(-0.5, -0.5, 0.5, 1.0)
    );    

    if(gl_VertexID == 0)
        v_color = vec4(1.0, 0.0, 0.0, 1.0);
    if(gl_VertexID == 1)
        v_color = vec4(0.0, 1.0, 0.0, 1.0);
    if(gl_VertexID == 2)
        v_color = vec4(0.0, 0.0, 1.0, 1.0);

    gl_Position = pos[gl_VertexID];
}