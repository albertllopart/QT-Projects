#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D cTexture;

uniform float accept;
//uniform sampler2D colorTexture;

void main()
{
    vec3 result = texture2D(cTexture, TexCoords).rgb;
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > accept)
        FragColor = vec4(result, 1.0);
    else
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}
