varying vec3 normal;
varying vec3 sup;
varying vec2 texture_coordinate;

void main(void)
{
	// Obt�m a posi��o do v�rtice em coordenadas de c�mera
	sup = vec3(gl_ModelViewMatrix * gl_Vertex);

	// E a normal, tamb�m em coordenadas de c�mera
	normal = gl_NormalMatrix * gl_Normal;	
	
	// Calcula posi��o do v�rtice
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Passa a coordenada de textura da unidade 0 para o Fragment Shader
	texture_coordinate = vec2(gl_MultiTexCoord0);
}

