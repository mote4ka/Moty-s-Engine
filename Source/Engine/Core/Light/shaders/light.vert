#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 scale;

void main(){
	//gl_Position = view * projection * model * vec4(aPos.x * scale.x, aPos.y * scale.y, aPos.z * scale.z, 1.0f);
	gl_Position = projection * view * model * vec4(aPos * vec3(0.4f), 1.0);
}