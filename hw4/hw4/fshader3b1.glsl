#extension GL_EXT_gpu_shader4 : require

#ifdef GL_ES
precision mediump float;	// set default precision to medium
#endif

varying	vec2	  v_TexCoord;	// varying variable for passing texture coordinate from vertex shader
uniform	sampler2D u_Sampler;	// uniform variable for the texture image
uniform int u_TextureEnabled;

flat varying vec3 v_Normal;

void main() {
	vec4 color;
	if (u_TextureEnabled == 1) {
			color = texture2D(u_Sampler, v_TexCoord);
	} else {
			//color = vec4(1.0, 1.0, 1.0, 1.0);
			color = vec4(v_Normal, 1.0);
	}
	gl_FragColor = color;
}
