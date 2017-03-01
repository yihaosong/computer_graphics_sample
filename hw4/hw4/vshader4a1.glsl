#ifdef GL_ES
precision mediump float;	// set default precision to medium
#endif

attribute vec3  a_Position;	// attribute variable: position vector
attribute vec2  a_TexCoord;	// varying variable for passing texture to fragment shader
uniform	  mat4	u_Model;
uniform	  mat4	u_View;
uniform	  mat4	u_Projection;
varying vec2 v_TexCoord;

void main() {

	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1);
  v_TexCoord = a_TexCoord;
}
