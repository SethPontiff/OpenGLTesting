#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;  // Add this

uniform sampler2D tex0;  // Add this

void main()
{
   FragColor = texture(tex0, texCoord);  // Or mix with color: texture(tex0, texCoord) * vec4(color, 1.0);
}