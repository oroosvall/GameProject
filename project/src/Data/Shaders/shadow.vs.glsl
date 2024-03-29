#version 410

layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 depthMVP;

void main()
{
	gl_Position =  depthMVP * vec4(vertexPosition_modelspace,1);
}