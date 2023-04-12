#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 u_model;
uniform mat4 u_viewProjection;
uniform vec3 u_cameraPos = vec3(0.0f ,0.0f, 0.0f);

void main()
{
    TexCoord = aTexCoord;

    vec3 objPos = vec3(u_model * vec4(aPos, 1.0));
    vec3 lookDir = normalize(u_cameraPos - objPos);
    vec3 upDir = vec3(0.0, 1.0, 0.0);

    vec3 rightDir = cross(vec3(0.0, 1.0, 0.0), lookDir);
    if (length(rightDir) < 0.001)
    {
        rightDir = cross(vec3(0.0, 0.0, 1.0), lookDir);
    }
    rightDir = normalize(rightDir);
    upDir = cross(lookDir, rightDir);

    mat3 lookMat = mat3(rightDir, upDir, -lookDir);
    mat4 lookMat4 = mat4(lookMat);
    gl_Position = u_viewProjection * u_model * lookMat4 * vec4(aPos, 1.0);
} 