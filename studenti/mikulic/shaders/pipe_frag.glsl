#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


// Ouput data
out vec4 FragColor;
//in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

//uniform vec3 lightPos;
uniform vec3 viewPos;
//uniform vec3 lightColor;
uniform vec3 objectColor;
uniform Material material;
uniform Light light;
//uniform sampler2D tekstura01;

void main()
{
    // ambient
    float ambientStrength = 0.2;
    //vec3 ambient = ambientStrength * light.ambient;
    vec3 ambient = light.ambient * material.ambient;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    float diff = clamp( abs(dot(norm, lightDir)), 0, 1);
    //float diff = abs(dot(norm, lightDir));
    vec3 diffuse =  light.diffuse * (diff * material.diffuse);

    // specular
    float specularStrength = 0.9;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    //float cosAlpha = clamp( dot( viewDir,reflectDir ), 0, 1 );
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    //vec3 specular = specularStrength * pow(cosAlpha, material.shininess) * light.specular;
    vec3 specular =  light.specular * (spec * material.specular);
    //vec3 tekstura_diffuse = texture(tekstura01, UV).rgb;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
