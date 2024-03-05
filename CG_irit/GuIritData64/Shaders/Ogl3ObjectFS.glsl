#version 150                                                               
                                                                            
struct Light                                                                
{                                                                           
    vec4 Ambient;                                                           
    vec4 Diffuse;                                                           
    vec4 Specular;                                                          
    vec4 Position;                                                          
};                                                                          
                                                                            
layout(std140) uniform Lighting                                             
{                                                                           
    Light Lights[8];                                                        
    vec4 AmbientIntensity;                                                  
    int NumLights;                                                          
};                                                                          
                                                                            
layout(std140) uniform FragmentCamera                                       
{                                                                           
    vec3 CameraPosition;                                                    
};                                                                          
                                                                            
layout(std140) uniform Material                                             
{                                                                           
    vec4 MaterialColor;                                                     
    float MaterialFactor;                                                   
    float SpecularPower;                                                    
    float SpecularIntensity;                                                
    bool UseTexture;                                                        
};                                                                          
                                                                            
layout(std140) uniform Fog                                                  
{                                                                           
    vec4 FogColor;                                                          
    float FogStartZ;                                                        
    float FogEndZ;                                                          
    float FogDensity;                                                       
    int FogType;                                                            
};                                                                          
                                                                            
uniform sampler2D DiffuseMap;                                               
                                                                            
in vec3 v_world_position;                                                   
in vec3 v_world_normal;                                                     
in vec2 v_tex_coord;                                                        
in vec4 v_color;                                                            
                                                                            
out vec4 out_color;                                                         
                                                                            
float saturate(float x)                                                     
{                                                                           
    return clamp(x, 0.0, 1.0);                                              
}                                                                           
                                                                            
vec3 saturate(vec3 x)                                                       
{                                                                           
    return clamp(x, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));              
}                                                                           
                                                                            
vec4 sampleTextureIfAny(vec2 texCoord)                                      
{                                                                           
    if (UseTexture)                                                         
        return texture(DiffuseMap, texCoord);                               
    else                                                                    
        return vec4(1.0, 1.0, 1.0, 1.0);                                    
}                                                                           
                                                                            
vec3 fromSrgb(vec3 col)                                                     
{                                                                           
    return pow(col, vec3(2.2, 2.2, 2.2));                                   
}                                                                           
                                                                            
vec4 fromSrgb(vec4 col)                                                     
{                                                                           
    return vec4(fromSrgb(col.rgb), col.a);                                  
}                                                                           
                                                                            
vec3 applyFog(vec3 color)                                                   
{                                                                           
    if (FogType == 0)                                                       
        return color;                                                       
                                                                             
    float distToEye = length(CameraPosition - v_world_position);             
    float fogFactor = 0;                                                     
    if (FogType == 1)                                                        
        fogFactor = saturate(exp(-FogDensity * distToEye));                  
    else if (FogType == 2)                                                   
        fogFactor = saturate(exp(-pow(FogDensity * distToEye, 2.0)));        
    else if (FogType == 3)                                                   
        fogFactor = saturate((FogEndZ - distToEye) / (FogEndZ - FogStartZ)); 
    return mix(FogColor.rgb, color, fogFactor);                              
}                                                                            
                                                                             
void main()                                                                 
{                                                                           
    vec3 toEye = normalize(CameraPosition - v_world_position);              
    vec3 normal = normalize(v_world_normal);                                
                                                                            
    vec3 ambientLightingSum = fromSrgb(AmbientIntensity.rgb);               
    vec3 diffuseLightingSum = vec3(0.0, 0.0, 0.0);                          
    vec3 specularLightingSum = vec3(0.0, 0.0, 0.0);                         
    for (int i = 0; i < NumLights; i++)                                             
    {                                                                               
        ambientLightingSum += fromSrgb(Lights[i].Ambient.rgb);                      
        vec3 toLight = normalize(Lights[i].Position.xyz - v_world_position);        
        float diffuseFactor = saturate(dot(toLight, normal));                       
        diffuseLightingSum += diffuseFactor * fromSrgb(Lights[i].Diffuse.rgb);      
        float specularFactor =                                                      
            pow(saturate(dot(toEye, reflect(-toLight, normal))), SpecularPower)     
            * SpecularIntensity                                                     
            * diffuseFactor;                                                        
        specularLightingSum += specularFactor * fromSrgb(Lights[i].Specular.rgb);   
    }                                                                               
                                                                                    
    vec4 vertexColor = mix(v_color, MaterialColor, MaterialFactor) *                
                       sampleTextureIfAny(v_tex_coord);                     
    vertexColor = fromSrgb(vertexColor);                                    
                                                                            
    vec3 finalColor =                                                       
        saturate(ambientLightingSum + diffuseLightingSum)                   
        * vertexColor.rgb                                                   
        * fromSrgb(sampleTextureIfAny(v_tex_coord).rgb)                     
        + specularLightingSum;                                              
    finalColor = applyFog(saturate(finalColor));                            
    out_color = vec4(finalColor, vertexColor.a);                            
}                                                                           
