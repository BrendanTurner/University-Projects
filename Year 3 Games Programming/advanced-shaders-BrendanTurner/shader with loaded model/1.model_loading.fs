#version 330 core
out vec4 FragColor;

struct Hatch {
    sampler2D hatch0;
    sampler2D hatch1;
    sampler2D hatch2;
    sampler2D hatch3;
    sampler2D hatch4;
    sampler2D hatch5;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

//ins
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//uniforms
uniform vec4 hatchColour;
uniform vec3 viewPos;
uniform int filter;
uniform Hatch hatch;
uniform SpotLight spotLight;
uniform sampler2D texture_diffuse1;
uniform float shininess;

//function prototypes
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 hatching(vec3 fcolor);

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    FragColor = texture(texture_diffuse1, TexCoords);
    FragColor += vec4(CalcSpotLight(spotLight, norm, FragPos, viewDir),0.0);
    if(filter==1)
    {
    FragColor = hatching(vec3(FragColor));
    }
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_diffuse1, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

//hatching code
vec4 hatching(vec3 fcolor)
{
    vec4 c;
    float shading = dot(fcolor,vec3(0.299,0.587,0.114));//convert to greyscale
    float step = 1.0/6.0;
    if( shading <= step )
    {   
        c = mix( texture( hatch.hatch5, TexCoords ), texture( hatch.hatch4, TexCoords ), 6. * shading );
    }
    if( shading > step && shading <= 2. * step )
    {
        c = mix( texture( hatch.hatch4, TexCoords ), texture( hatch.hatch3, TexCoords) , 6. * ( shading - step ) );
    }
    if( shading > 2. * step && shading <= 3. * step )
    {
        c = mix( texture( hatch.hatch3, TexCoords ), texture( hatch.hatch2, TexCoords ), 6. * ( shading - 2. * step ) );
    }
    if( shading > 3. * step && shading <= 4. * step )
    {
        c = mix( texture( hatch.hatch2, TexCoords ), texture( hatch.hatch1, TexCoords ), 6. * ( shading - 3. * step ) );
    }
    if( shading > 4. * step && shading <= 5. * step )
    {
        c = mix( texture( hatch.hatch1, TexCoords ), texture( hatch.hatch0, TexCoords ), 6. * ( shading - 4. * step ) );
    }
    if( shading > 5. * step )
    {
        c = mix( texture( hatch.hatch0, TexCoords ), vec4( 1. ), 6. * ( shading - 5. * step ) );
    }
    vec4 src = mix( mix( hatchColour, vec4( 1. ), c.r ), c, .5 );
    return src;
}