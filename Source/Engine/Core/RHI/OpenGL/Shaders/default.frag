#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 CurrentPos;
in vec3 color;
in vec2 texCoord;

uniform vec3 Rotation;

uniform vec3 CamPos;

struct Material{
	sampler2D BaseColor;
	sampler2D SpecularTexture;
	float shineFac;
};
uniform Material mat;
struct Light{
	vec3 Position;
	vec3 Direction;

	int Type;
	vec4 Color;
	float Power;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

void main()
{
	vec3 LightDirection;
	float att = 1.0f;

	switch(light.Type){
		//Directional Light
		case 0:
			LightDirection = normalize(-light.Direction);
			break;
		//Point light
		case 1:
			LightDirection = normalize(light.Position - CurrentPos);
			//vec3 fadeFac = vec3(1.0f, 0.14f, 0.07f);
			vec3 fadeFac = vec3(1.0f, 0.09f, 0.032f);
			float Distance = length(light.Position - CurrentPos);
			att = light.Power / (fadeFac.x + fadeFac.y * Distance + fadeFac.z * (Distance*Distance));
			break;
	}
	//Ambient Lighting
	//vec3 Ambient = light.ambient * att * vec3(texture(mat.BaseColor, texCoord));
	vec3 Ambient = light.ambient * att * vec3(texture(mat.BaseColor, texCoord));

	//Diffuse Lighting
	vec3 normalVec = normalize(Normal);

	float diffuse = max(dot(normalVec, LightDirection), 0.0f);
	float gamma = 1.0f;
	vec3 Diffuse = light.diffuse * att * diffuse * pow(texture(mat.BaseColor, texCoord).rgb, vec3(gamma)) * vec3(light.Power);

	//Specular Lighting
	vec3 viewDirection = normalize(CamPos - CurrentPos);
	//blinn-phong stuff
	vec3 halfwayDirection = normalize(LightDirection + viewDirection);
	vec3 reflectDirection = reflect(-LightDirection, normalVec);
	//float specular = mat.shineFac * pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	float specular = mat.shineFac * pow(max(dot(Normal, halfwayDirection), 0.0), 32);
	vec3 Specular = light.specular * att * specular * vec3(texture(mat.SpecularTexture, texCoord));

	//Light result
	vec4 LightResult = light.Color * vec4(Ambient + Diffuse + Specular, 1.0f);
	
	//Output
	FragColor =  LightResult;
}