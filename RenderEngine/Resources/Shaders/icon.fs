#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec3 u_color = vec3(1.0f, 1.0f, 1.0f);

void main()
{
    vec4 texColor = texture(u_Texture, TexCoord);
    vec3 invColor = vec3(1.0f) - texColor.rgb;
    FragColor = vec4(invColor, texColor.a) * vec4(u_color, 1.0f);
} 