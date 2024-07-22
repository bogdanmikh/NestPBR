#version 330

#define USE_BUMP_MAPPING 1
#define PBR 1
#define USE_SHADOW 1
#define SOFT_SHADOW 1
#define AO 1

uniform float iTime;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform vec3 iColor;

uniform sampler2D iChannel0;

float PI = 3.14159265359;

float uvMultiply = 2.0;
float bumpScale = 35.0;

float metalness = 0.0;
float roughness = 0.4;
vec3 albedo = vec3(1.0);
vec3 lightColor = vec3(1.0, 0.7, 0.56);

float getHeight(sampler2D channel, vec2 offset) {
    return bumpScale * texture(channel, uvMultiply * offset / iResolution.xy).r;
}


float calcShadow(vec3 lightPos, vec3 pos) {
    vec3 lightDir = normalize(lightPos - pos);
    vec3 currPos = pos + lightDir * 0.005; // avoid self-shadow
    float baseHeight = texture(iChannel0, uvMultiply * (pos.xy + 0.5)).r;

    float stapSize = 0.05;
    int step = 0;
    int maxStep = 30;
    float heights[3] = float[3](0.0, 0.0, 0.0);
    while(distance(currPos, lightPos) > 0.01 && step < maxStep) {
        step += 1;
        currPos += lightDir * 0.01;
        heights[2] = heights[1];
        heights[1] = heights[0];
        heights[0] = texture(iChannel0, uvMultiply * (currPos.xy + 0.5)).r;
        if(heights[0] - currPos.z > baseHeight) {
            #if SOFT_SHADOW
            float shadow = float(step) / float(maxStep);
            #else
            float shadow = 0.0;
            #endif

            return clamp(shadow, 0.3, 1.0);
        }
    }
    return 1.0;
}

float calcAmbientOcclision(vec2 TexCoord) {
    float baseSample = getHeight(iChannel0, TexCoord);
    int samples = 2;
    float occlusion = 0.0;
    for(int i = -samples; i < samples; i++) {
        for(int j = -samples; j < samples; j++) {
            float currSample = getHeight(iChannel0, TexCoord + vec2(i,j));
            occlusion += (currSample >= baseSample ? 1.0 : 0.0);
        }
    }
    occlusion = 1.0 - occlusion / float(samples * samples * 4);
    return occlusion;
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 claclLightBRDF(vec3 lightPos, vec3 viewDir, vec3 pos, vec3 normal) {
    vec3 lightDir = lightPos - pos;
    float distance = length(lightDir);
    distance = distance * distance;
    lightDir = normalize(lightDir);
    vec3 h = normalize(lightDir + viewDir);
    float attenuation = 1.0 / distance;
    vec3 radiance = lightColor * attenuation;
    float cosTheta = max(0.0, dot(h, viewDir));
    float NdotL = max(dot(normal, lightDir), 0.0);


    vec3 F0 = mix(vec3(0.04), albedo, metalness);
    vec3 F = FresnelSchlick(cosTheta,F0);
    float D = DistributionGGX(normal, h, roughness);
    float G = GeometrySmith(normal, viewDir, lightDir, roughness);
    float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * NdotL + 0.001;
    vec3 specular = (D * G * F) / denominator;

    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS) * (1.0 - metalness);

    vec3 Lo = (kD * albedo / PI + specular) * radiance * NdotL;

    vec3 ambient = 0.2 * lightColor * albedo;
    vec3 color = ambient + Lo;

    return color;
}


float calcDiffuse(vec3 lightDir, vec3 normal) {
    return max(dot(normal, lightDir), 0.0);
}

float calcSpecular(vec3 lightDir, vec3 viewDir, vec3 normal) {
    vec3 h = normalize(lightDir + viewDir);
    float spec = dot(normal, h);
    return pow(max(spec, 0.0), 16.0);
}

//blinn-phong light
vec3 calcLight(vec3 lightPos, vec3 viewDir, vec3 pos, vec3 normal) {
    vec3 lightDir = lightPos - pos;
    float distance = length(lightDir);
    distance = distance * distance;
    lightDir = normalize(lightDir);
    vec3 h = normalize(lightDir + viewDir);
    float attenuation = 1.0 / distance;
    float diffuse = calcDiffuse(lightDir, normal);
    float specular = calcSpecular(lightDir, viewDir, normal);

    float ambient = 0.5;

    return lightColor * attenuation * (diffuse * specular + ambient);
}

vec3 getNormal(vec2 TexCoord) {
    float height = getHeight(iChannel0, TexCoord.xy);
    float upHeight = getHeight(iChannel0, TexCoord.xy + vec2(0,-1));
    float rightHeight = getHeight(iChannel0,TexCoord.xy + vec2(1,0));

    return normalize(vec3(height - upHeight, height - rightHeight, 1.0));
}

//in vec2 TexCoord;
out vec4 fragColor;

void main()  {
    vec2 TexCoord = gl_FragCoord.xy / iResolution;
    vec3 lightPos = vec3((iMouse.xy/iResolution.xy - 0.5), 0.5);
    vec3 fragPos = vec3((TexCoord/iResolution.xy - 0.5), 0.0);

    #if USE_BUMP_MAPPING
    vec3 normal = getNormal(TexCoord);
    #else
    vec3 normal = vec3(0.0, 0.0, 1.0);
    #endif

    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0) - fragPos);
    vec3 lightDir = normalize(lightPos - fragPos);
    #if PBR
    vec3 light = claclLightBRDF(lightPos, viewDir, fragPos, normal);
    #else
    vec3 light = calcLight(lightPos, viewDir, fragPos, normal);
    #endif

    #if AO
    float occlusion = calcAmbientOcclision(TexCoord);
    #else
    float occlusion = 1.0;
    #endif

    #if USE_SHADOW
    //Don’t compute shadows for objects not facing the light source
    float shadow = dot(lightDir, normal) > 0.0? calcShadow(lightPos, fragPos): 1.0;
    #else
    float shadow = 1.0;
    #endif

    fragColor = vec4(light * occlusion * shadow, 1.0);
}