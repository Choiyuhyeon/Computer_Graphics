#version 150                                                               
                                                                            
layout(std140) uniform Transform                                            
{                                                                           
    mat4 World;                                                             
    mat4 WorldInverseTranspose;                                             
};                                                                          
                                                                            
layout(std140) uniform AdditionalTransform                                  
{                                                                           
    float ZOffset;                                                          
    float NormalCoeff;                                                      
};                                                                          
                                                                            
layout(std140) uniform VertexCamera                                         
{                                                                           
    mat4 View;                                                              
    mat4 Projection;                                                        
    vec3 ZOffsetTarget;                                                     
};                                                                          
                                                                            
in vec3 in_position;                                                        
in vec3 in_normal;                                                          
in vec2 in_tex_coord;                                                       
in vec4 in_color;                                                           
                                                                            
out vec3 v_world_position;                                                  
out vec3 v_world_normal;                                                    
out vec2 v_tex_coord;                                                       
out vec4 v_color;                                                           
                                                                            
void main()                                                                 
{                                                                           
    vec4 worldPosition = vec4(in_position, 1.0) * World;                    
    vec3 zOffsetDir = normalize(ZOffsetTarget - worldPosition.xyz);         
    worldPosition += vec4(zOffsetDir * ZOffset, 0.0);                       
    gl_Position = worldPosition * View * Projection;                        
    v_world_position = worldPosition.xyz;                                   
    v_world_normal = (vec4(in_normal * NormalCoeff, 0.0) *                  
                      WorldInverseTranspose).xyz;                           
    v_tex_coord = in_tex_coord;                                             
    v_color = in_color;                                                     
}                                                                           
