#type vertex
#version 330 core

out vec2 v_FragCoord;

layout(location = 0) in vec3 a_Position;		

void main()
{
	gl_Position = vec4(a_Position, 1.0f);
	v_FragCoord = gl_Position.xy;
}; 


#type fragment
#version 330 core

layout(location = 0) out vec4 color;
			
in vec2 v_FragCoord;


float focalLength = 2.0;
float aspectRatio = 16.0 / 9.0;
float viewportHeight = 2.0;
vec3 cameraLocation = vec3(0, 0, 0);


struct ray
{
	vec3 origin;
	vec3 direction;
};

vec3 rayAt(ray r, float t) { return r.origin + t * r.direction; }

vec3 rayColor(ray r);
	
bool hitSphere(vec3 center, float radius, ray r);

void main()
{
	vec3 viewportPoint = vec3(v_FragCoord * vec2(aspectRatio, 1.0) * 0.5 * viewportHeight, focalLength);
	ray r;
	r.origin = cameraLocation;
	r.direction = normalize(viewportPoint - cameraLocation);				
	color = vec4(rayColor(r), 1.0);
}

vec3 rayColor(ray r)
{
	if(hitSphere(vec3(0, 0, 3), 0.75, r))
	{
		return vec3(1, 0, 0);
	}

	vec3 color;
	float t = r.direction.y * 0.5 + 0.5;
	color = t * vec3(0.5, 0.7, 1.0) + (1 - t) * vec3(1);
	return color;
}

bool hitSphere(vec3 center, float radius, ray r)
{
	vec3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = 2.0 * dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float d = b * b - 4 * a * c;
	return d >= 0;
}