#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D floorTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{          
    float distance = length(vec3(lightPos - FragPos));
    float attenuation = min(100.0 / (distance * distance),1.0);
    vec3 color = texture(floorTexture, TexCoords).rgb;
    // ambient
    vec3 ambient = 0.05 * color;
    
    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 128.0);

    vec3 specular = (vec3(color) + vec3(1.0)) * 0.1 * spec; // assuming bright white light color
    //vec3 composante_color = (ambient + diffuse + specular) * attenuation;
    vec3 composante_color = (ambient + diffuse + specular);
    FragColor = vec4(composante_color, 1.0);

}