#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D diffuseMap;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	// Ambient lighting
	float ambientStrength = 0.05;
	vec3 ambient = ambientStrength * lightColor;
	 // distance effect
    float distance = length(vec3(lightPos - FragPos));
    float attenuation = min(100.0 / (distance * distance),1.0);
 

	// Diffuse lighting

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * lightColor;
	
	// Final result
	vec3 result = (ambient + diffuse) * texture(diffuseMap,TexCoord).xyz * attenuation;
	FragColor = vec4(result,1.0f);
}