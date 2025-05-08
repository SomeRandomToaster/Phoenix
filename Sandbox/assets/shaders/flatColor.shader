#type vertex
#version 330 core

out vec3 v_Position;
out vec3 v_Color;

layout(location = 0) in vec3 a_Position;
			
uniform mat4 u_ProjectionViewMatrix;	
uniform mat4 u_Transform;		

void main()
{
	gl_Position = u_ProjectionViewMatrix * u_Transform * vec4(a_Position, 1.0f);
	v_Position = gl_Position.xyz;
}; 


#type fragment
#version 330 core

layout(location = 0) out vec4 color;
			
in vec3 v_Position;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}