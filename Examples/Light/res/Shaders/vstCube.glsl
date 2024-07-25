#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 TexCoord;

void main() {
    vec4 pos = u_model * u_projection * u_view * vec4(aPos, 1.0);
    pos = vec4(aPos * 0.8, 1.0);
    gl_Position = u_model * vec4(aPos * 0.3, 1.0);
    TexCoord = aPos;
}