#version 300 es
//smooth in vec4 theColor;

smooth in vec2 UV;
out vec3 outputColor;
uniform sampler2D myTextureSampler;

void main()
{
	outputColor = texture( myTextureSampler, UV ).rgb;
}
