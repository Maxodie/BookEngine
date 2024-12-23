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
#define PI 3.14159265358979323846

// max lights
#define MAX_LIGHTS 10

in Vertex
{
    vec3 Position;
    vec3 Normal;
} vertex;

struct Material
{
    float Roughness;
    float Metallic;
    vec3 Albedo;
};

struct PointLight
{
    float Intensity;
    vec3 Radiance;
    vec3 Position;
};

uniform PointLight u_pointLights[MAX_LIGHTS];
uniform int u_nbrPointLight;

uniform Material u_material;
uniform vec3 u_viewPos;

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return num / denom;
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return num / denom;
}

float GeometrySmithGGX(float NdotV, float NdotL, float roughness)
{
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 ComputePointLights(vec3 N, vec3 V, vec3 F0)
{
    vec3 result = vec3(0.0);

    for(int i = 0; i < u_nbrPointLight; ++i)
    {
        // compute parameters
        vec3 L = normalize(u_pointLights[i].Position - vertex.Position);
        vec3 H = normalize(L + V);
        float NdotL = max(dot(N, L), 0.0);
        float NdotV = max(dot(N, V), 0.0);

        // Cook-Torrance (BRDF)
        float NDF = DistributionGGX(N, H, u_material.Roughness);
        vec3 FS = FresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
        float GS = GeometrySmithGGX(NdotV, NdotL, u_material.Roughness);

        // diffuse light
        vec3 diffuse = (vec3(1.0) - FS) * (1.0 - u_material.Metallic);

        // specular light
        vec3 specular = (NDF * GS * FS) / max(4.0 * NdotV * NdotL, 0.0001);

        // light attenuation
        float distance = length(u_pointLights[i].Position - vertex.Position);
        float attenuation = u_pointLights[i].Intensity / (distance * distance);

        // combine components
        result += (diffuse * u_material.Albedo / PI + specular) * u_pointLights[i].Radiance * attenuation * NdotL;

        //break if max light
        if(i >= MAX_LIGHTS - 1)
        {
            break;
        }
    }
    return result;
}

void main()
{
    // normalized surface normal
    vec3 N = normalize(vertex.Normal);

    // camera view direction
    vec3 V = normalize(u_viewPos - vertex.Position);

    // fresnel base reflection
    vec3 F0 = mix(vec3(0.04f), u_material.Albedo, u_material.Metallic);

    // point lights contribution
    vec3 result = ComputePointLights(N, V, F0);

    // final color calculation
    out_fragment = vec4(result, 1.0);
}

++FRAGMENT++
