#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform sampler2D emissionMap;

uniform float vision_coeff;
uniform vec3 lightColor;

void main()
{           
    // obtain normal from normal map in range [0,1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * -2.0 + 1.0);  // this normal is in tangent space

    // get diffuse color
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    
    // ambient
    vec3 ambient = 0.1 * color;
    
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    // specular for Blinn Phong (with halfWayVec instead of reflect vector)
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * vec3(texture(specularMap,fs_in.TexCoords));

    // emission
    vec3 emission = texture(emissionMap, fs_in.TexCoords).rgb;

    float distance = length(vec3(fs_in.TangentLightPos - fs_in.TangentFragPos));
    float attenuation = min(vision_coeff / (distance * distance),1.0);
    vec3 lighting = (ambient + diffuse + specular + emission) * attenuation * lightColor;
    
    FragColor = vec4(lighting, 1.0);
}