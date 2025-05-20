##vertex =========================================
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texcoord;

out vec2 uTexcoord;
uniform mat4 u_MVP;

void main(){


	gl_Position =  u_MVP * vec4(aPos, 1.0);
	uTexcoord = texcoord;

}

##fragment =======================================
#version 330 core

out vec4 FragColor;

in vec2 uTexcoord;
uniform sampler2D texture1;
vec3  u_Color;

void main(){
	u_Color = vec3(1.0, 0.8, 1.0);
	FragColor = texture(texture1, uTexcoord) * vec4(u_Color , 1.0);
}