#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

// camera
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow* window, float dt)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.ProcessKeyboard(FORWARD, dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(BACKWARD, dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(LEFT, dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(RIGHT, dt);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	cam.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

class RendererWindow {

	int width;
	int height;
	GLFWwindow* win{ nullptr };

public:


	// Constructor
	RendererWindow(int w, int h, const char* title) {

		width = w;
		height = h;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->create(w, h, title);
		glfwMakeContextCurrent(win);

		glfwMakeContextCurrent(win);
		glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
		glfwSetCursorPosCallback(win, mouse_callback);
		glfwSetScrollCallback(win, scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	GLFWwindow* getWindow() { return win; }
	void swapBuffers() const { glfwSwapBuffers(win); }
	void pollEvents() const { glfwPollEvents(); }

	int getWidth() { return width; }
	int getHeight() { return height; }


	~RendererWindow() {
		glfwDestroyWindow(win);
		glfwTerminate();
	}
};



class Renderer {

public:

	virtual void setupDraw() {};

	virtual void draw(GLFWwindow* win) {}

	virtual ~Renderer() {
		glfwTerminate();
	}

};


#endif // RENDERER_H