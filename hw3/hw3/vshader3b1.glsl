#ifdef GL_ES
precision mediump float;	// set default precision to medium
#endif

attribute vec3		a_Position;	// attribute variable: position vector
attribute vec2		a_TexCoord;	// attribute variable: texture coordinate
uniform   mat4  u_Modelview;	// uniform variable for modelview matrix
uniform   mat4  u_Projection;	// uniform variable for projection matrix
varying vec2	v_TexCoord;	// varying variable for passing texture coordinate to fragment shader

void main() {

	gl_Position = u_Projection * u_Modelview * vec4(a_Position, 1);
	v_TexCoord = a_TexCoord;
}
