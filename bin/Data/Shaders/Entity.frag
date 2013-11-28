#version 150

in vec4 WorldPos;
in vec3 Norm;
in vec2 UV;

uniform sampler2D Texture;

out vec4 outputF;

void main()
{
    vec3 n2 = normalize(Norm);
    float Lighting = max(dot(n2, vec3(0,0,1)),0.6);
    //outputF = vec4(UV,0,1);
    outputF = vec4(texture(Texture, UV)) * Lighting;
}
