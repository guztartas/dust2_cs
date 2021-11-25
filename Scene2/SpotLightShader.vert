varying vec3 normal;
varying vec3 sup;
varying vec2 texture_coordinate;

void main(void)
{
	// Obtém a posição do vértice em coordenadas de câmera
	sup = vec3(gl_ModelViewMatrix * gl_Vertex);

	// E a normal, também em coordenadas de câmera
	normal = gl_NormalMatrix * gl_Normal;	
	
	// Calcula posição do vértice
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Passa a coordenada de textura da unidade 0 para o Fragment Shader
	texture_coordinate = vec2(gl_MultiTexCoord0);
}

