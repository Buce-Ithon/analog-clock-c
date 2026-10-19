#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;

uniform sampler2D texture0;
uniform sampler2D noiseTexture;
uniform vec4 colDiffuse;
uniform float time;

float stepfun(float x)
{
    return (sign(x) + 1.0) / 2.0;
}

float square(vec2 pos)
{
    return stepfun(pos.x + 1.0) * stepfun(1.0 - pos.x) *
           stepfun(pos.y + 1.0) * stepfun(1.0 - pos.y);
}

vec2 distort(vec2 pos)
{
    vec2 offset = pos + vec2(cos(time * 2.0) / 8.0,
                             sin(time * 2.0) / 8.0);
    vec2 noise = texture(noiseTexture, (offset - 0.5) * 5.0).xy;

    // Direct adaptation of the Shadertoy distortion, with iChannel1 mapped
    // to the repeatable noise texture created by frosted_background.h.
    return pos + square((offset - 0.5) * 5.0) * noise * 0.05;
}

void main()
{
    vec4 source = texture(texture0, distort(fragTexCoord));

    // A pure-colour source has nothing for refraction to reveal.  The fine
    // grain and cool haze make the frosted surface visible in that case too.
    float grain = texture(noiseTexture, fragTexCoord * 96.0 + time * 0.015).r - 0.5;
    vec3 colour = mix(source.rgb, vec3(0.90, 0.94, 1.00), 0.10);
    colour += grain * 0.035;

    // Preserve the alpha written by ClearBackground(backgroundColor), so the
    // transparent raylib window continues to show the desktop underneath.
    finalColor = vec4(clamp(colour, 0.0, 1.0), source.a) * colDiffuse * fragColor;
}
