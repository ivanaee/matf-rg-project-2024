//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));

    Normal = mat3(transpose(inverse(model))) * aNormal;

    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}


//#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;
uniform vec3 dirLightDirection;
uniform vec3 dirLightColor;
uniform vec3 pointLightPosition;
uniform vec3 pointLightColor;
uniform vec3 spotLightPosition;
uniform vec3 spotLightDirection;
uniform vec3 spotLightColor;

uniform float spotLightCutOff;
uniform float spotLightOuterCutOff;

void main()
{
    vec4 textureColor = texture(texture_diffuse1, TexCoords);
    vec3 objectColor = textureColor.rgb;
    vec3 norm = normalize(Normal);

    // Directional light
    vec3 lightDir = normalize(-dirLightDirection);

    // Ambient
    vec3 ambient = 0.20 * dirLightColor * objectColor;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * dirLightColor * objectColor;

    // Blinn-Phong specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = 0.25 * spec * dirLightColor;

    vec3 directionalResult = ambient + diffuse + specular;

    // Point light - campfire
    vec3 pointLightDir = normalize(pointLightPosition - FragPos);

    float pointDiff = max(dot(norm, pointLightDir), 0.0);
    vec3 pointDiffuse =
        pointDiff * pointLightColor * objectColor;

    vec3 pointHalfwayDir =
        normalize(pointLightDir + viewDir);

    float pointSpec =
        pow(max(dot(norm, pointHalfwayDir), 0.0), 32.0);

    vec3 pointSpecular =
        0.25 * pointSpec * pointLightColor;

    // Light attenuation
    float distance =
        length(pointLightPosition - FragPos);

    float attenuation =
        1.0 /
        (1.0
         + 0.09 * distance
         + 0.032 * distance * distance);

    vec3 pointAmbient =
        0.05 * pointLightColor * objectColor;

    vec3 pointResult =
        (pointAmbient + pointDiffuse + pointSpecular)
        * attenuation;

    // Spotlight - flashlight attached to camera
    vec3 spotLightDir =
        normalize(spotLightPosition - FragPos);

    float theta =
        dot(
            spotLightDir,
            normalize(-spotLightDirection)
        );

    float epsilon =
        spotLightCutOff - spotLightOuterCutOff;

    float intensity =
        clamp(
            (theta - spotLightOuterCutOff) / epsilon,
            0.0,
            1.0
        );

    // Diffuse
    float spotDiff =
        max(dot(norm, spotLightDir), 0.0);

    vec3 spotDiffuse =
        spotDiff * spotLightColor * objectColor;

    // Blinn-Phong specular
    vec3 spotHalfwayDir =
        normalize(spotLightDir + viewDir);

    float spotSpec =
        pow(
            max(dot(norm, spotHalfwayDir), 0.0),
            32.0
        );

    vec3 spotSpecular =
        0.25 * spotSpec * spotLightColor;

    vec3 spotResult =
        (spotDiffuse + spotSpecular) * intensity;


    // Final lighting
    vec3 result =
        directionalResult
        + pointResult
        + spotResult;

    FragColor = vec4(result, textureColor.a);
}