#version 330 core
uniform mat4 projection_matrix;
uniform mat4 model_matrix;

uniform vec4 light_pos = vec4(0.0, 0.0, 75.0, 1.0);
uniform vec3 light_dir = vec3(0.0, 0.0, -1.0);
uniform float cutoff = 0.99;
uniform vec4 ambientProduct = vec4(0.2, 0.2, 0.2, 1.0);
uniform vec4 diffuseProduct = vec4(1.0, 0.8, 0.0, 1.0);
uniform vec4 specularProduct = vec4(1.0, 1.0, 1.0, 1.0);
uniform float shine = 100.0;


in vec3 fN;
in vec3 fE;
in vec4 pixelPos;

out vec4  fColor;

void main() 
{ 
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	vec3 L = normalize(light_pos.xyz - pixelPos.xyz);

	vec3 H = normalize( L+E );
	vec4 ambient = ambientProduct;

	float Kd = max(dot(L, N), 0.0);
	float Ks = pow(max(dot(N, H), 0.0), shine);
	
	vec4 diffuse = Kd * diffuseProduct;
	vec4 specular = Ks * specularProduct;
	if(dot(L, N) < 0.0) specular = vec4(0.0, 0.0, 0.0, 1.0);



	float theta = max(-dot(L, light_dir), 0.0);

	if(theta > cutoff){
		fColor = ambient+diffuse+specular;
	}
	else{
		fColor = ambient;
	}
	fColor.a = 1.0;
} 

