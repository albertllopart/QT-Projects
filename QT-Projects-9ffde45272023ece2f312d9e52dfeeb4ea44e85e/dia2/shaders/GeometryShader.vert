#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
//layout(location = 3) in vec3 diffuse;
//layout(location = 4) in vec4 specular;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

out Data
{
    vec3 positionViewspace;
    vec3 normalWorldspace;
    vec2 texCoord;
    //vec3 diffuse;
    //vec4 specular;

}VSOut;

void main(void)
{

    VSOut.positionViewspace = (modelViewMatrix * vec4(position, 1)).xyz;
    VSOut.normalWorldspace = normal;
    VSOut.texCoord = texCoord;

    gl_Position = projectionMatrix * vec4(VSOut.positionViewspace, 1.0);
}
