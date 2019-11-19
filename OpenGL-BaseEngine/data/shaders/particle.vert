#version 430 core

#define SCALE 0.1f

layout (location = 0) in vec3 vertex;
layout(std140, binding = 0) restrict buffer Data_Pos {
	vec4 position[];
};

uniform mat4 projection;
uniform vec3 camRight;
uniform vec3 camUp;

out vec3 color;

void main() {
	vec3 billboard = position[gl_InstanceID].xyz 
		+ camRight * vertex.x * SCALE
		+ camUp * vertex.y * SCALE;
	
	color = 1.0f - normalize(position[gl_InstanceID].xyz);
	
	gl_Position = projection * vec4(billboard, 1.0f);
}
