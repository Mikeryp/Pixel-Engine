#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 PX_projection;

out vec4 col;


uniform vec2 mouse;

float dist(vec2 a, vec2 b)
{
	return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}


void main()
{
	gl_Position = PX_projection * vec4(position.xyz, 1);
	col = color;
}






#shader fragment
#version 330 core

in vec4 col;
out vec4 o_color;

uniform vec2 mouse;


float dist(vec2 a, vec2 b)
{
	return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

float map(float val, float ly1, float ly2, float r1, float r2) {
	return (val - ly1) / (ly2 - ly1) * (val - ly1) + r2;
}

void main()
{	
	vec2 mpos = vec2(mouse.x, -mouse.y + 400);
	o_color = col *(9 / dist(mpos, gl_FragCoord.xy));
}
