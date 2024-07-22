#version 330

in vec2 TexCoord;

uniform float iTime;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform vec3 iColor;

uniform sampler2D texture1;

out vec4 fragColor;

void main() {
    vec2 st = gl_FragCoord.xy / iResolution;
    vec2 m = gl_FragCoord.xy / iMouse;
    fragColor = vec4(0, 1, 1, 1.) * texture(texture1, TexCoord);
}