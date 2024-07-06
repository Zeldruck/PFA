#version 330 core

in vec2 texCoord;

uniform vec4 ourColor;
uniform sampler2D ourTexture1;

out vec4 fragColor;

void main()
{
    fragColor = texture(ourTexture1, texCoord) * ourColor;
} 