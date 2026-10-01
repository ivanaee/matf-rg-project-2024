//#shader vertex
#version 330 core

out vec2 TexCoords;

const vec2 positions[3] = vec2[](
    vec2(-1.0, -1.0),
    vec2( 3.0, -1.0),
    vec2(-1.0,  3.0)
);

const vec2 texCoords[3] = vec2[](
    vec2(0.0, 0.0),
    vec2(2.0, 0.0),
    vec2(0.0, 2.0)
);

void main()
{
    gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    TexCoords = texCoords[gl_VertexID];
}


//#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float grayscaleAmount;

void main()
{
    vec3 color = texture(screenTexture, TexCoords).rgb;

    float gray =
        dot(color, vec3(0.299, 0.587, 0.114));

    vec3 grayscaleColor = vec3(gray);

    vec3 result =
        mix(color, grayscaleColor, grayscaleAmount);

    FragColor = vec4(result, 1.0);
}