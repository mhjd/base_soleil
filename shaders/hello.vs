#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec4 mpos;
out vec3 mnormal;
out vec2 tcoord;
uniform float weight;

void main() {
     gl_Position = vec4(pos, weight);
     mpos = vec4(pos, 1.0);
     tcoord = texCoord;
     mnormal = normal;
}
