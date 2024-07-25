#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 TexCoord;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
//    gl_Position = vec4(aPos, 1.0);
    TexCoord = aPos;
}