#version 430 core
#define SCALE 0.005f

layout (location = 0) in vec3 vertex;

uniform mat4 projection;

void main(){
	mat4 view = mat4(1.0f);
	
	gl_Position = projection * view * vec4(vertex.xy * SCALE, -0.25f, 1.0f);
}