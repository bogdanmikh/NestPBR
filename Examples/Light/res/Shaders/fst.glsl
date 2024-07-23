#version 330

in vec2 TexCoord;

uniform float iTime;
uniform vec2 iResolution;
uniform vec2 iMouse;
//uniform vec3 iColor;

uniform sampler2D texture1;
uniform samplerCube iSky;

out vec4 fragColor;

void main() {
    vec2 st = gl_FragCoord.xy / iResolution;
    float pebbleHeight = texture(texture1, TexCoord).r;
    vec3 normal = vec3(pebbleHeight, 1.0 - pebbleHeight, 0.0);
    vec3 reflectedDirection = reflect(normalize(vec3(TexCoord, 1.0)), normal);
    vec2 m = gl_FragCoord.xy / iMouse;
    vec4 skyColor = texture(iSky, reflectedDirection);
    vec4 color = vec4(pebbleHeight, pebbleHeight, pebbleHeight, 1.0);
    fragColor = mix(color, skyColor, 0.5);
}