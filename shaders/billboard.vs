#version 400

layout (location = 0) in vec3 vPos;

uniform mat4 uTransform;
uniform vec3 uOffset;
uniform vec4 uColor;
uniform mat4 uVP;

out vec4 color;
out vec2 uv;

void main()
{
   color = uColor;
   uv = vPos.xy;
   gl_Position = uVP * uTransform * vec4(vPos, 1.0); 
}
