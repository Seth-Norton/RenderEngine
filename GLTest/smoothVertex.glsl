#version 330 core

uniform mat4 projection_matrix;
uniform mat4 model_matrix;

in  vec4 vPosition;
in  vec4 vColor;
in	vec4 vNormal;
out vec3 fN;
out vec3 fE;

out vec4 pixelPos;

void main() 
{
	fN = normalize(vec3(model_matrix * vec4(vNormal.xyz, 0.0)));
	fE = -vPosition.xyz;
	pixelPos = model_matrix*vPosition;


	gl_Position = projection_matrix*model_matrix*vPosition;
} 
