#version 430

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;
/*TODO:: Complete your shader code for a full Phong shading*/ //Week--5

uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity

uniform vec3 Ka;			// Ambient reflectivity    ##added for lab exercise
uniform vec3 La;			// Ambient light intensity ##added for lab exercise

uniform vec3 Ks;			// Specular refelectivity  ##added for lab exercise
uniform vec3 Ls;			// Specular light intensity##added for lab exercise
uniform float n =8.0;

//Week--5: complete to a full phong shading
layout( location = 0 ) out vec4 FragColour;

void main() {

   //Calculate the light vector
   vec3 L = normalize(lightPos - vertPos);  

   //calculate Ambient light Intensity making sure it is not negative
   //##added for lab exercise
   vec4 Ia = vec4(La,1.0) * vec4(Ka,1.0);
    
   //calculate Diffuse Light Intensity making sure it is not negative 
   vec4 Id = vec4(Ld,1.0) * vec4(Kd,1.0) * max(dot(N,L), 0.0);

   //calculate Specular light Intensity making sure it is not negative
   //##added for lab exercise
   vec3 viewv = normalize(-vertPos);
   vec3 refl = reflect(-L,N);
   vec4 Is;
   if(dot(L,viewv)>0.0)
   {
   Is = vec4(Ls,1.0) * vec4(Ks,1.0) * pow(max(0.0,dot(viewv,refl)),n);
   }


   //Multiply the Reflectivity by the Diffuse intensity
   //and is clamped 0 to 1     
   FragColour = clamp(Ia+Id+Is, 0.0, 1.0);

}
