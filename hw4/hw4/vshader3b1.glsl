// vertex shader
#version 130
#extension GL_EXT_gpu_shader4 : require

#ifdef GL_ES
precision mediump float;	// set default precision to medium
#endif

attribute vec3		a_Position;	// attribute variable: position vector
attribute vec2		a_TexCoord;	// attribute variable: texture coordinate
uniform   mat4  u_Modelview;	// uniform variable for modelview matrix
uniform   mat4  u_Projection;	// uniform variable for projection matrix
varying vec2	v_TexCoord;	// varying variable for passing texture coordinate to fragment shader
attribute vec3 a_Normal;
flat varying vec3 v_Normal;

void main() {

	gl_Position = u_Projection * u_Modelview * vec4(a_Position, 1);
	v_TexCoord = a_TexCoord;
	v_Normal = a_Normal;
}
