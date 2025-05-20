##vertex =========================================
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 u_model, u_view, u_projection;

void main(){

	gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

##fragment =======================================
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;
vec3 uColor;


void main(){
	uColor = vec3(1.0, 1.0, 0.0);
	FragColor = texture(texture1, TexCoord) * vec4(uColor, 1.0);
}