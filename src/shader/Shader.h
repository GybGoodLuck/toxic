#include <string>

static const char verticesSource[] = R"(

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexcoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main() {
    TexCoords = aTexcoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

)";

static const char fragmentSource[] = R"(

#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoords);
}

)";

static const char screenVerticesSource[] = R"(

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main() {
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

)";

static const char screenFragmentSource[] = R"(

#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D texture1;

void main()
{
    vec3 color = texture(texture1, TexCoords).rgb;
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    FragColor = vec4(average, average, average, 1.0);
}

)";