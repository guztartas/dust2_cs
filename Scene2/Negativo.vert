uniform vec3 lightPos;
varying vec3 N, L;

void main(void)
{
	// vertex MVP transform
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	// eye-space normal
	N = gl_NormalMatrix * gl_Normal;
	
	// eye-space light vector
	vec4 V = gl_ModelViewMatrix * gl_Vertex;
	L = lightPos - V.xyz;
	
	// Copy the primary color
	gl_FrontColor = gl_Color;
}

