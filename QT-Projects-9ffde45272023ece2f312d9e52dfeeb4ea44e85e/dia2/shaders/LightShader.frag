#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;


struct Light {
    vec3 Position;
    vec3 Color;
    float Intensity;
    float Radius;
    int TypeLight; // 0 == Directional | 1 == PointLight

    float Linear;
    float Quadratic;
};

uniform sampler2D gAlbedo;
uniform sampler2D gNormal;
uniform sampler2D gPosition;

uniform int NumberLightsInScene;
const int MaxLight = 32;
uniform Light lights[MaxLight];
uniform vec3 viewPos;

uniform int renderView;

vec3 PointLight(int index, vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular, vec3 lighting, vec3 viewDir)
{
    vec3 lightRet = vec3(0, 0, 0);
    // Calculate distance between light source and current fragment
    float distance = length(lights[index].Position - FragPos);
    if(distance < lights[index].Radius)
    {
        // Diffuse
        vec3 lightDir = normalize(lights[index].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[index].Color;

        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular = lights[index].Color * spec * Specular;

        // Attenuation
        float attenuation = lights[index].Intensity / (1.0 + lights[index].Linear * distance + lights[index].Quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lightRet = diffuse + specular;
    }
    return lightRet;
}

vec3 DirectionalLight(int index, vec3 FragPos, vec3 Normal, vec3 Diffuse, float Specular, vec3 lighting, vec3 viewDir)
{
    vec3 lightRet = vec3(0, 0, 0);
    // Diffuse
    vec3 lightDir = normalize(lights[index].Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[index].Color;

    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
    vec3 specular = lights[index].Color * spec * Specular;

    // Attenuation
    //float distance = length(lights[index].Position - FragPos);
    //lights[index].Intensity
    //float attenuation = lights[index].Intensity / (1,0 + lights[index].Linear * distance + lights[index].Quadratic * distance * distance);
    //diffuse *= attenuation;
    //specular *= attenuation;
    lightRet = diffuse + specular;
    return lightRet;
}

void main(void)
{
    // Retrieve data from gbuffer
    vec3 FragPos = texture2D(gPosition, TexCoords).rgb;
    vec3 Normal = texture2D(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture2D(gAlbedo, TexCoords).rgb;
    float Specular = texture2D(gAlbedo, TexCoords).a;

    // Then calculate lighting as usual
    vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
    vec3 viewDir  = normalize(viewPos - FragPos);

    if (renderView != 0)
    {
        if (renderView == 1)
        {
            FragColor = vec4(Diffuse, 1.0);
        }
        else if (renderView == 2)
        {
            FragColor = vec4(Normal, 1.0);
        }
        else if (renderView == 3)
        {
            FragColor = vec4(FragPos, 1.0);
        }
        else
        {
            FragColor = vec4(1.0,0.0,1.0,1.0);
        }
    }
    else
    {
        vec3 lightingOut = lighting;
        //lightingOut = DirectionalLight(0, FragPos, Normal, Diffuse, Specular, lightingOut, viewDir);
        for (int i = 0; i < NumberLightsInScene; i++)
        {
            if(lights[i].TypeLight == 0)
                lightingOut += DirectionalLight(i, FragPos, Normal, Diffuse, Specular, lightingOut, viewDir);
            if(lights[i].TypeLight == 1)
                lightingOut += PointLight(i, FragPos, Normal, Diffuse, Specular, lightingOut, viewDir);
        }
        // = DirectionalLight(FragPos, Normal, Diffuse, Specular, lighting, viewDir);
        //FragColor = vec4(lighting, 1.0);
        FragColor = vec4(lightingOut, 1.0);
    }
}
