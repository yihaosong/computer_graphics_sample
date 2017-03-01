varying vec3 Color;
varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

void main(){
	// light emission properties
	vec3 LightColor = vec3(1,1,1);

	// material properties
	vec3 MaterialDiffuseColor  = Color;
	vec3 MaterialAmbientColor  = vec3(0.2,0.2,0.2) * MaterialDiffuseColor;
	//vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);
	vec3 MaterialSpecularColor = vec3(1.0,1.0,1.0);

	// normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );

	// direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );

	// cosine of the angle between the normal and the light direction (clamped above 0)
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendiular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0.0, 1.0);

	// eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);

	// direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);

	// cosine of the angle between the Eye vector and the Reflect vector (clamped to 0)
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0.0,1.0 );

	// Ambient : simulates indirect lighting
	// Diffuse : "color" of the object
	// Specular : reflective highlight, like a mirror
	gl_FragColor = vec4((MaterialAmbientColor +
		       0.5 * cosTheta * MaterialDiffuseColor * LightColor +
		       0.5 * pow(cosAlpha,50.0) * MaterialSpecularColor * LightColor) , 1.0);
}
