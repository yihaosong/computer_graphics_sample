#ifdef GL_ES
precision mediump float;	// set default precision to medium
#endif

attribute vec3  a_Position;	// attribute variable: position vector
uniform	  mat4	u_Model;
uniform	  mat4	u_View;
uniform	  mat4	u_Projection;


void main() {
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1);
}
