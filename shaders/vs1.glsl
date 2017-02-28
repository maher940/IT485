#version 300 es
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;
//smooth out vec4 theColor;
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;


smooth out vec2 UV;
uniform mat4 MVP;
void main()
{
	gl_Position = MVP * vec4(position, 1.0f);
	//theColor = color;
	UV = vertexUV;
}
