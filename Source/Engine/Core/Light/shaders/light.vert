#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 CamMatrix;
uniform mat4 model;
uniform vec3 scale;

void main(){
	gl_Position = CamMatrix * model * vec4(aPos.x * scale.x, aPos.y * scale.y, aPos.z * scale.z, 1.0f);
}