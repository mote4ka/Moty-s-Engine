#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texCoord;
out vec3 Normal;
out vec3 CurrentPos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 uv;

void main()
{
	//gl_Position = view * projection * vec4( vec3( model * vec4( aPos.x * scale.x, aPos.y * scale.y, aPos.z * scale.z, 1.0f) ), 1.0f );
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	color = aColor;
	texCoord = vec2(aTex.x * uv.x, aTex.y * uv.y);
	Normal = mat3(transpose(inverse(model))) * aNormal;
	CurrentPos = vec3(model * vec4(aPos, 1.0f));
}