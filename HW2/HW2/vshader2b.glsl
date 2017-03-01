attribute vec2  a_Position;	// attribute variable: position vector
attribute vec3  a_Color;	// attribute variable: color vector
varying   vec4  v_Color;	// varying variable for passing color to fragment shader
uniform   float u_theta;
uniform   int   u_ReverseColor;	// reverse color flag
uniform   int  u_twist;

mat4 rotation;
//rotation modifier
float r_mod;
void main() {
	if (u_twist == 1) {
			r_mod = length(a_Position);
	} else {
			r_mod = 1.0;
	}
  rotation = mat4(
  	vec4(cos(u_theta*r_mod),sin(u_theta*r_mod),0,0),  //first column
  	vec4(-sin(u_theta*r_mod),cos(u_theta*r_mod),0,0), //second column
  	vec4(0,0,1,0),           			//third column
  	vec4(0,0,0,1)         				//fourth column
	);
	//gl_Position = gl_ModelViewProjectionMatrix * u_ModelMatrix;
	gl_Position = gl_ModelViewProjectionMatrix * rotation * vec4(a_Position, 0, 1);
	if (u_ReverseColor == 1)
		v_Color = vec4(1.0-a_Color.r, 1.0-a_Color.g, 1.0-a_Color.b, 1.0);
	else	v_Color	= vec4(a_Color, 1);
}
