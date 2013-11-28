#version 150

in vec3 Vertex;
in vec3 Normal;
in vec2 Uv;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

out vec4 WorldPos;
out vec3 Norm;
out vec2 UV;

void main()
{
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Vertex, 1);
    WorldPos = ModelViewMatrix * vec4(Vertex,1);
    Norm = NormalMatrix * Normal;
    UV = Uv;
}
