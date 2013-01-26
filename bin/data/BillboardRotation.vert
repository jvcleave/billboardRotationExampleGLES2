attribute vec4 position;
attribute vec4 color;
attribute vec4 normal;
attribute vec2 texcoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

varying vec4 colorVarying;
varying vec2 texCoordVarying;

attribute float		pointSize;
attribute  float	angle;
varying  float		rotAngle;

/*void main() {
	
	rotAngle = angle;

	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 eyeCoord  = gl_ModelViewMatrix * gl_Vertex;
	gl_Position    = gl_ProjectionMatrix * eyeCoord;
	float dist     = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	   = 600.0 / dist;
	gl_PointSize   = pointSize * att;	
	gl_FrontColor  = gl_Color;
	
	
}*/





void main()
{
	rotAngle = angle;
	colorVarying = color;
	texCoordVarying = texcoord;
	
	vec4 eyeCoord = modelViewMatrix * position;
	gl_Position = projectionMatrix * eyeCoord;
	
	float dist = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	 = 600.0 / dist;
	gl_PointSize = pointSize * att;

}


