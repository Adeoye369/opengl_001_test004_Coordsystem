#include <iostream>

#include <sstream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "PrimitiveMesh.h"

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

class RenderTriangle : public Renderer {

public:
	unique_ptr<GraphicObject> triangleObject;
	unique_ptr<GraphicObject> rectObject;
	unique_ptr<GraphicObject> cubeObject;



	Renderer::Renderer;

	void setupDraw() override{
		Renderer::setupDraw();

		glEnable(GL_DEPTH_TEST);

		//// Vertices
		//vector<VertexInfo> triangleVertices;
		//// TODO: set layout order in VertexInfo
		//// 
		//								// Position      // texCoord
		//VertexInfo::attribComponentCount = { 3,  2 };
	
		//triangleVertices.push_back({ -0.5f, -0.5f, 0.0f, 1.0f, 1.0f });
		//triangleVertices.push_back({ 0.5f, -0.5f, 0.0f, 1.0f, 0.0f });
		//triangleVertices.push_back({ 0.0f, 0.5f, 0.0f,  0.0f, 0.0f });
		//
		//triangleObject = make_unique<GraphicObject>(triangleVertices);
		//triangleObject->initShader("src/basic01.shader");
		//triangleObject->initTexture("images/wall.jpg");
		//triangleObject->objShader->setVec3("uColor", 0.1f, 0.5f, 1.0f);
		//
		//triangleObject->translate(glm::vec3(0.5f, 0.0f, 0.0f));
		//triangleObject->rotate(180.0f, glm::vec3(0.0f, 0.0f, 1.0f));


			//=============== Rectangle Object ==================================


		MeshData rectMesh = GetRectangleMesh();
		rectObject = make_unique<GraphicObject>(rectMesh.mesh, rectMesh.indices);
		rectObject->initShader("src/basic01.shader");
		rectObject->initTexture("images/picture186.png");




		// ================= Cube Object Draw =======================	
		cubeObject = make_unique<GraphicObject>(GetCubeMesh());
		cubeObject->initShader("src/basic01.shader");
		cubeObject->initTexture("images/wall.jpg");

	}

	void draw() override {
		Renderer::draw();
		

		glClearColor(0.1f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		glm::mat4 camView;
		camView = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		cubeObject->initMVP( camView);
		cubeObject->rotate((float)glfwGetTime()*5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		cubeObject->scale(0.5f);

		cubeObject->bindTexture();
		cubeObject->draw();

		cubeObject->resetModel();
		cubeObject->translate(glm::vec3(1.0f, 0.5f, 0));
		cubeObject->rotate((float)glfwGetTime()*30.0f, glm::vec3(1, 0, 0));
		cubeObject->draw();

		cubeObject->resetModel();
		cubeObject->translate(glm::vec3(-2.0f, -0.5f, 0));
		cubeObject->rotate((float)glfwGetTime() * 30.0f, glm::vec3(0, 0.5, 1));
		cubeObject->draw();

		// Testing Passing View and Projection to initMVP
		glm::mat4 rectView = glm::mat4(1.0f);
		rectView = glm::translate(rectView, glm::vec3(0.0f, 0.0f, -3.0f));

		rectObject->initMVP(cubeObject->getView(), cubeObject->getProjection());
		rectObject->rotate(-80.f, glm::vec3(1.0f, 0.0f, 0.0f));
		rectObject->scale(4.0f, 4.0f, 4.0f);

		rectObject->bindTexture();
		rectObject->draw();

		rectObject->rotate(30.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		rectObject->scale(0.5f);
		rectObject->draw();
	}

	virtual ~RenderTriangle(){}
};



int main()
{

	RendererWindow win(800, 600, "some title");

	RenderTriangle triangle;
	triangle.setupDraw();

	while (!win.mainloop()) {

		triangle.draw();

		win.swapBuffers();
		win.pollEvents();
	}



}