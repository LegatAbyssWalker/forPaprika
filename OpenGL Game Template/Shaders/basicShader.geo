#version 460

layout (points) in;
layout (triangle_strip, max_vertices = 2) out;

void buildQuad(vec4 position) {
	gl_Position = gl_in[0].gl_Position + vec4(-1, 0.0, 0.0, 0.0); 
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(1, 0.0, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}

void main() {
	 buildQuad(gl_in[0].gl_Position);
};