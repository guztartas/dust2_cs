varying vec3 N, L;

void main (void)
{
	// output the diffuse color
	float intensity = max(0.0, dot(normalize(N), normalize(L)));
	
	gl_FragColor.rgb = (1.0 - gl_Color.rgb) * intensity;
	gl_FragColor.a = 1.0;
}
