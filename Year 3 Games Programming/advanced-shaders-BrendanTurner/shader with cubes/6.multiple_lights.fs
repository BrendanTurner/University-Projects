#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Hatch {
    sampler2D hatch0;
    sampler2D hatch1;
    sampler2D hatch2;
    sampler2D hatch3;
    sampler2D hatch4;
    sampler2D hatch5;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec4 hatchColour;
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;
uniform Hatch hatch;

//toggles
uniform int filter;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 hatching(vec3 fcolor);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    //FragColor = vec4(result, 1.0);
    FragColor = hatching(result);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
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
    float shading2=1-shading;
    if(filter==4)//greyscale normal code
    {
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
    }
    if(filter==5)//inverted greyscale code
        {
        if( shading2 <= step )
        {   
            c = mix( texture( hatch.hatch5, TexCoords ), texture( hatch.hatch4, TexCoords ), 6. * shading2 );
        }
        if( shading2 > step && shading2 <= 2. * step )
        {
            c = mix( texture( hatch.hatch4, TexCoords ), texture( hatch.hatch3, TexCoords) , 6. * ( shading2 - step ) );
        }
        if( shading2 > 2. * step && shading2 <= 3. * step )
        {
            c = mix( texture( hatch.hatch3, TexCoords ), texture( hatch.hatch2, TexCoords ), 6. * ( shading2 - 2. * step ) );
        }
        if( shading2 > 3. * step && shading2 <= 4. * step )
        {
            c = mix( texture( hatch.hatch2, TexCoords ), texture( hatch.hatch1, TexCoords ), 6. * ( shading2 - 3. * step ) );
        }
        if( shading2 > 4. * step && shading2 <= 5. * step )
        {
            c = mix( texture( hatch.hatch1, TexCoords ), texture( hatch.hatch0, TexCoords ), 6. * ( shading2 - 4. * step ) );
        }
        if( shading2 > 5. * step )
        {
            c = mix( texture( hatch.hatch0, TexCoords ), vec4( 1. ), 6. * ( shading2 - 5. * step ) );
        }
    }
    vec4 src = mix( mix( hatchColour, vec4( 1. ), c.r ), c, .5 );
    c = vec4(vec3(shading),1.0);
    vec4 cn = vec4(vec3(shading2),1.0);
    float invr=1.0-fcolor.r;
    float invg=1.0-fcolor.g;
    float invb=1.0-fcolor.b;
    vec4 neg = vec4(invr,invg,invb,1.0);
    if(filter==0)//no filter
    {
        return vec4(vec3(fcolor),1.0);
    }
    if(filter==1)//greyscale
    {
        return c;
    }
    if(filter==2)//negative greyshade
    {
        return cn;
    }
    if(filter==3)//negative
    {
    return neg;
    }
    if(filter==4)//crosshatch on normal greyscale
    {
        return src;
    }
    if(filter==5)//crosshatch on inverted greyscale
    {
        return src;
    }
}