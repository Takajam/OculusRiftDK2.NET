#version 330

out vec4 outputColor;

uniform sampler2D Texture0;

in vec2 oTexCoord0;
in vec2 oTexCoord1;
in vec2 oTexCoord2;
in float oVignette;

void main() {
    float r = texture(Texture0, oTexCoord0).r;
    float g = texture(Texture0, oTexCoord1).g;
    float b = texture(Texture0, oTexCoord2).b;

    outputColor = vec4(r, g, b, 1) * oVignette;
}