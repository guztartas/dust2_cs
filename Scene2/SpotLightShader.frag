varying vec3 normal;
varying vec3 sup;
uniform float interna;	// cos do �ngulo onde come�a a borda interna do spot
varying vec2 texture_coordinate; 
uniform sampler2D my_color_texture;

void main (void)
{
	// Calcula um vetor da superf�cie � luz
	vec3 luz = normalize(gl_LightSource[0].position.xyz - sup); 

	// O vetor da superf�cie ao observador � simplesmente o oposto de sup
	// pois j� estamos em coordenadas de c�mera: observador = (0,0,0)
	vec3 obs = normalize(-sup);
	
	// Calcula vetor m�dio
	vec3 medio = normalize(luz+obs);

	// Normaliza a normal interpolada
	vec3 normal = normalize(normal);

	// Calcula �ngulo entre dire��o do spot e vetor da luz � superf�cie
	float spot = max(dot(gl_LightSource[0].spotDirection, -luz),0.0);

	// Calcula intensidade da luz considerando a varia��o da borda interna � externa	
	// Se estiver fora do cone de luz, "borda" recebe 0.0
	float borda = smoothstep(gl_LightSource[0].spotCosCutoff,interna,spot);

	// Aplica GL_SPOT_EXPONENT ao resultado
	spot = pow(spot, gl_LightSource[0].spotExponent) * borda;

	// Calcula componente difuso
	vec4 difuso = (gl_FrontLightProduct[0].diffuse * max(dot(normal,luz), 0.0));
		
	// Calcula componente especular
	vec4 especular = gl_FrontLightProduct[0].specular 
		* pow(max(dot(normal,medio),0.0),gl_FrontMaterial.shininess);


	// Multiplica pela intensidade do spot e pela combina��o difuso+especular e adiciona
	// � contribui��o do componente ambiente do modelo de ilumina��o. 
	// Tamb�m passa a coordenada de textura com sua cor e multiplica para gerar a cor final
	// do fragmento
	gl_FragColor = (gl_FrontLightModelProduct.sceneColor + gl_FrontLightProduct[0].ambient
		+ spot * (difuso+especular)) * texture2D(my_color_texture, texture_coordinate);
}
