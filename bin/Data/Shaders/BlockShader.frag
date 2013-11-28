#version 150

in vec4 WorldPos;
in vec3 Norm;
in vec2 UV;

uniform sampler2D Texture;

out vec4 outputF;

void main()
{
    vec3 Normal = normalize(Norm);

    vec3 LightDir = WorldPos.xyz - vec3(0.0,0.0,0.0);
    float NdotL = max(dot(Normal, normalize(-LightDir)),0);
    float Atten, Distance;
    vec4 Color, DiffuseColor, AmbientColor;
    Distance = length(LightDir);
    
    if(NdotL > 0.0)
    {
        Atten = 1 + 0.2 * Distance + 0.1 * Distance * Distance;
	    DiffuseColor = vec4(vec3(1.0f,1.0f,1.0f), 1.0f) * 3.0f * NdotL;
        AmbientColor = vec4(vec3(1.0f,1.0f,1.0f), 1.0f) * 0.05;
        Color = DiffuseColor;
    }

    
    //outputF = vec4(UV,0,1);
    vec4 Albedo = texture(Texture, UV);
    outputF = Albedo * (Color/Atten) + (AmbientColor * Albedo);
}
