#version 330

in vec2 TexCoord;

uniform float iTime;
uniform vec2 iResolution;
uniform vec2 iMouse;
//uniform vec3 iColor;

uniform sampler2D texture1;
uniform samplerCube iSky;

out vec4 fragColor;

vec2 flip(vec2 r) {
    return vec2(-r.x, -r.y);
}

vec2 flip(vec3 r) {
    return vec2(-r.x, -r.y);
}

void main() {
    vec2 st = gl_FragCoord.xy / iResolution;
    float pebbleHeight = texture(texture1, TexCoord).r;
    vec3 normal = vec3(pebbleHeight, 1.0 - pebbleHeight, pebbleHeight);
    vec2 uv = TexCoord;
    uv += pebbleHeight * 0.1;
    vec3 reflectedDirection = vec3(uv - 0.7, sin(iTime) * 0.5 + 1.);
    reflectedDirection = vec3(flip(reflectedDirection), reflectedDirection.z);

    vec2 m = gl_FragCoord.xy / iMouse;
    vec4 skyColor = texture(iSky, reflectedDirection);
    vec4 color = vec4(pebbleHeight, pebbleHeight, pebbleHeight, 1.0);
    fragColor = mix(color, skyColor, 0.8);
}