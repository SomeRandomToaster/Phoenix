#type vertex
#version 330 core

out vec3 v_Position;
out vec2 v_TexCoord;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
			
uniform mat4 u_ProjectionViewMatrix;	
uniform mat4 u_Transform;		

void main()
{
	gl_Position = u_ProjectionViewMatrix * u_Transform * vec4(a_Position, 1.0f);
	v_Position = gl_Position.xyz;
	v_TexCoord = a_TexCoord;
}; 


#type fragment
#version 330 core

layout(location = 0) out vec4 color;
			
in vec3 v_Position;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
}