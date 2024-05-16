#version 150
out vec4 finalColor;

uniform vec4 fixedColor;

void main()
{
    finalColor = fixedColor;//clamp(fixedColor, 0, 1);
}
