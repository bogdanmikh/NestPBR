#version 330

out vec4 fragColor;

uniform float iTime;
uniform vec2 iResolution;
uniform vec2 iMouse;

void main() {
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}