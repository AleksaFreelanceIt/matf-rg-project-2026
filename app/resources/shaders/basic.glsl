//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    gl_Position = projection * view * vec4(FragPos, 1.0);
}

//#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform float emissionStrength;

void main()
{
    vec3 color = lightColor;
    float glow = 0.5 + 0.5 * max(dot(normalize(Normal), vec3(0.0, 1.0, 0.0)), 0.0);
    float intensity = emissionStrength * (0.7 + 0.3 * glow);
    
    vec3 result = color * intensity;
    FragColor = vec4(result, 1.0);
}