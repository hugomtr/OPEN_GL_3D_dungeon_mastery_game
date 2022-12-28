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
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float height_scale;
uniform float vision_coeff;
uniform vec3 lightColor;

vec2 ParallaxMappingCoordinate(vec2 texCoords, vec3 viewDir){
    const int numLayers = 20;
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy * height_scale;
    vec2 deltaTexCoords = P / numLayers;
    
    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;
    while (currentLayerDepth < currentDepthMapValue){
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }
    return currentTexCoords;
}

void main()
{           
    // offset texture coordinates with Parallax Mapping
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 texCoords = ParallaxMappingCoordinate(fs_in.TexCoords, viewDir);

    // if(texCoords.x > 1.02 || texCoords.y > 1.05 || texCoords.x < -0.02 || texCoords.y < -0.02)
    //     discard;

    // then sample textures with new texture coords and according to normal vector direction
    vec3 normal = texture(normalMap, texCoords).xyz;
    normal = normalize(normal * 2.0 - 1.0);

    // Blinn Phong lighting
    vec3 color = texture(diffuseMap,texCoords).xyz;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(halfwayDir, normal), 0.0),32.0);
    vec3 specular = 0.5f * spec * color;

    // distance effect
    float distance = length(vec3(fs_in.TangentLightPos - fs_in.TangentFragPos));
    float attenuation = min(vision_coeff*2.0f / (distance * distance),1.0);
    vec3 lighting = (ambient + diffuse + specular) * attenuation * lightColor;
    
    FragColor = vec4(lighting, 1.0);
}