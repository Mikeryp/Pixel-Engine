// comment


#shader vertex
#include"Struct.shstr"

#version 330 core

uniform mat4 PX_model;
uniform mat4 PX_view;
uniform mat4 PX_projection;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 FragCol;

void main() {
	gl_Position =  PX_projection * PX_view * PX_model * vec4(position, 1.0);
	FragCol = color;
}





#shader fragment

#version 330 core

uniform mat4 PX_model;
uniform mat4 PX_view;
uniform mat4 PX_projection;


in vec4 FragCol;
out vec4 FragColor;

void main() {
	FragColor = FragCol;
}