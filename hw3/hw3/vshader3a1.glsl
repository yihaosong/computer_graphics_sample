#define M_PI 3.1415926535897932384626433832795
attribute vec2  a_Position;	// attribute variable: position vector
attribute vec2  a_TexCoord;	// varying variable for passing texture to fragment shader
uniform	  mat4	u_ModelMatrix;
uniform   int	u_Twist;
uniform   float u_Theta;
varying   vec2  v_TexCoord;	// varying variable for passing texture to fragment shader

mat4 rotation;
//rotation modifier
float r_mod;
float angleRadians;

void main() {

angleRadians = u_Theta * M_PI / 180.0;

if (u_Twist == 1) {
			r_mod = length(a_Position);
	} else {
			r_mod = 1.0;
	}

	rotation = mat4(
  	vec4(cos(angleRadians*r_mod),sin(angleRadians*r_mod),0,0),  //first column
  	vec4(-sin(angleRadians*r_mod),cos(angleRadians*r_mod),0,0), //second column
  	vec4(0,0,1,0),           			//third column
  	vec4(0,0,0,1)         				//fourth column
	);

	gl_Position = gl_ModelViewProjectionMatrix * rotation * vec4(a_Position, 0, 1);
	v_TexCoord = a_TexCoord;
}
