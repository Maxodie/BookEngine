#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uvs;

out Vertex
{
    vec3 Position;
    vec3 Normal;
} vertex;

uniform mat4 u_model;
uniform mat4 u_proj;
uniform mat4 u_view;

void main()
{
    vertex.Normal = mat3(u_model) * a_normal;
    vertex.Position = vec3(u_model * vec4(a_position, 1.0));
    gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0f);
}

++VERTEX++

#version 330 core
layout (location = 0) out vec4 out_fragment;

in Vertex
{
    vec3 Position;
    vec3 Normal;
} vertex;

void main()
{
    vec3 lightPos = vec3(-0.5, 0.0, 1.0);// light Position
    vec3 lightRad = vec3(1.0, 1.0, 1.0);// light Radiance
    vec3 viewPos = vec3(0.0, 0.0, 2.0);// camera Position

    // Material properties
    vec3 albedo = vec3(0.3, 0.8, 0.8);// base color
    float roughness = 0.5;
    float metallic = 0.2;

    // Diffuse (Lambertian) Lighting
    vec3 N = normalize(vertex.Normal);
    vec3 lightDir = normalize(lightPos - vertex.Position);
    float diff = max(dot(N, lightDir), 0.0);
    vec3 diffuse = diff * lightRad;

    // Specular (Cook-Torrance) lighting
    vec3 viewDir = normalize(viewPos - vertex.Position);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float NdotH = max(dot(N, halfwayDir), 0.0);
    float roughnessSq = roughness * roughness;
    float denom = (NdotH * NdotH) * (roughnessSq - 1.0) + 1.0;
    float D = roughnessSq / (3.1415 * denom * denom);
    float kS = metallic;
    vec3 specular = lightRad * (kS * D);

    // Final color calculation
    vec3 color = (diffuse + specular) * albedo;

    out_fragment = vec4(color, 1.0);
}

++FRAGMENT++
