#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

class RendererWindow {


	int width;
	int height;
	GLFWwindow* win{ nullptr };

public:
	RendererWindow(int w, int h, const char* title) {

		width = w;
		height = h;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->create(w, h, title);
		glfwMakeContextCurrent(win);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			std::cout << "GLAD failed to load" << std::endl;


	}

	void create(int w, int h, const char* title) {
		win = glfwCreateWindow(w, h, title, NULL, NULL);
		if (!win) {
			std::cout << "GLFW failed to load" << std::endl;
			glfwTerminate();

		}
	}

	void makeContextCurrent() const { glfwMakeContextCurrent(win); }
	int mainloop() const { return glfwWindowShouldClose(win); }
	GLFWwindow* getWindow() const { return win; }
	void swapBuffers() const { glfwSwapBuffers(win); }
	void pollEvents() const { glfwPollEvents(); }

	int getWidth() { return width; }
	int getHeight() { return height; }

};



class Renderer {

public:
	
	Renderer() = default;

	virtual void setupDraw() {};

	virtual void draw() {}

	virtual ~Renderer() {
		glfwTerminate();
	}


};


#endif // RENDERER_H