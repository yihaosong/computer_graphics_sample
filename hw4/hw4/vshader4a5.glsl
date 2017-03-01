// input vertex data; different for all executions of this shader
attribute vec3  a_Position;	// attribute variable: position vector
attribute vec2  a_TexCoord;	// attribute variable: texture coordinate
attribute vec3  a_Color;	// attribute variable: color vector
attribute vec3  a_Normal;	// attribute variable: vertex normal

// output data; will be interpolated for each fragment
varying vec2 v_TexCoord;
varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform vec3 u_LightDirection;

void main(){
	// output position of the vertex, in clip space : MVP * position
	gl_Position =  u_Projection * u_View * u_Model * vec4(a_Position, 1);

	// position of the vertex, in worldspace : M * position
	Position_worldspace = (u_Model * vec4(a_Position, 1)).xyz;

	// vector that goes from the vertex to the camera, in camera space;
	// in camera space, the camera is at the origin (0,0,0).
	EyeDirection_cameraspace = vec3(0,0,0) - ( u_View * u_Model * vec4(a_Position, 1)).xyz;

	// vector that goes from the vertex to the light, in camera space
	LightDirection_cameraspace = (u_View*vec4(u_LightDirection,0)).xyz;

	// normal of the the vertex, in camera space
	Normal_cameraspace = ( u_View * u_Model * vec4(a_Normal, 0)).xyz;

	// only correct if ModelMatrix does not scale the model! Use its inverse transpose if not.
	v_TexCoord = a_TexCoord;
}
