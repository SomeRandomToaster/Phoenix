#type vertex
#version 330 core

layout(location = 0) in vec3 a_LocalPosition;
			
out vec3 v_WorldPosition;
out vec3 v_LocalPosition;


uniform mat4 u_ProjectionViewMatrix;	
uniform mat4 u_Transform;		

void main()
{
	gl_Position = u_ProjectionViewMatrix * u_Transform * vec4(a_LocalPosition, 1.0f);
	v_WorldPosition = gl_Position.xyz;
	v_LocalPosition = a_LocalPosition;
}; 


#type fragment
#version 330 core
			
in vec3 v_WorldPosition;
in vec3 v_LocalPosition;

layout(location = 0) out vec4 o_Color;


uniform vec3 u_Color;

void main()
{
	float radius = 1.0;
	float borderRadius = 0.85;
	float borderThickness = 0.05;
	float innerCircleRadius = 0.2;
	float auxCircleRadius = 0.1;
	float auxCircleDist = 0.5;
	float alpha = 1 - step(radius, length(v_LocalPosition));
	vec3 color = mix(vec3(0), u_Color, step(borderThickness, abs(length(v_LocalPosition) - borderRadius)));
	color = mix(vec3(0), color, step(innerCircleRadius, length(v_LocalPosition)));
	color = mix(vec3(0), color, step(auxCircleRadius, length(v_LocalPosition - vec3(0, auxCircleDist, 0))));

	o_Color = vec4(color, alpha);
}