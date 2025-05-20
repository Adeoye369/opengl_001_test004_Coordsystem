
#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

using std::vector, std::cout, std::endl, std::string, std::unique_ptr, std::make_unique;


struct VertexInfo {

	// store the actual vertex data
	vector<float> vertex{};



	
	// attribute count as in the coordinate x, y, z
	// index           0            1           2
	// e.g count       3            2           3
	//             0.5, 0.2, 0.4,  1.0, 1.0,  0.5, 0.5, 0.0
	static inline vector<unsigned int> attribComponentCount;


		// total count of layout
	static inline unsigned int stride{};

	VertexInfo() = default;

	VertexInfo(std::initializer_list<float> v) : vertex(v){

		stride = vertex.size() * sizeof(float);

	}


};

class GraphicObject{
	vector<VertexInfo> verticesInfo;
	vector<float>vertices{};
	vector<unsigned int>indices{};

	unsigned int VBO{}, IBO{};

	bool hasIBO{}, hasTexture{};


	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;

	void setupVBO() {

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * VertexInfo::stride, vertices.data(), GL_STATIC_DRAW);

	}

	void setupIBO() {

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * VertexInfo::stride, indices.data(), GL_STATIC_DRAW);
	
	}

	void setupObject() {

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		setupVBO();
		if(hasIBO) setupIBO();
	
		// for all layout
		int offset = 0;
		for (int i = 0; i < VertexInfo::attribComponentCount.size(); i++){
			
			// attribut component component eg. x, y => (2); x,y,z => (3),
			int attribCompCount = VertexInfo::attribComponentCount[i];
			glVertexAttribPointer(
				i,									// index
				attribCompCount,	// component count
				GL_FLOAT,							// component type
				GL_FALSE,							// Normalize?
				VertexInfo::stride,					// vertex attributes stride
				(void*)(offset * sizeof(float))); // vertex attribute offset

			glEnableVertexAttribArray(i);

			offset += attribCompCount;
		}

		glBindVertexArray(0);
	}


public:
	unsigned int VAO;
	Shader* objShader;
	Texture* tex1;

	GraphicObject(vector<VertexInfo> verticesInfos) {
		this->verticesInfo = verticesInfos;

		//append the vertices
		for (size_t i = 0; i < verticesInfos.size(); i++)
			vertices.insert(vertices.end(), verticesInfos[i].vertex.begin(), verticesInfos[i].vertex.end());

		hasIBO = false;

		setupObject();
	};


	GraphicObject(vector<VertexInfo>verticesInfos, vector<unsigned int>indices) {
		this->verticesInfo = verticesInfos;

		//append the vertices
		for (size_t i = 0; i < verticesInfos.size(); i++)
			vertices.insert(vertices.end(), verticesInfos[i].vertex.begin(), verticesInfos[i].vertex.end());


		this->indices = indices;
		hasIBO = true;

		setupObject();
	}

	void initShader(const char* shaderPath){

	objShader = new Shader(shaderPath);

	// make sure to initialize matrix to identity matrix first
	model = view = projection = glm::mat4(1.0f); 

	}

	// === TEXTURE RELATED =============================

	void initTexture(const char* texturePath) {
		hasTexture = true;
		tex1 = new Texture(texturePath);
		objShader->useProgram();
		objShader->setInt("texture1", 0);
	}

	void bindTexture(unsigned int slot = 0) {
		tex1->bindTexture(slot);
	}

	void unBindTexture() {
		tex1->unBindTexture();
	}




	//// === PROJECTION RELATED========================
	//GraphicObject& setProjection(glm::mat4 projection ) {
	//
	//	// If projection is specified, use it
	//	this->projection = projection;
	//	objShader->useProgram();
	//	objShader->setMat4("u_projection",  this->projection);
	//	return *this;
	//}
	//
	//void setPerspective(float fov, float aspect, float near, float far) {
	//	this->projection = glm::perspective(glm::radians(fov), aspect, near, far);
	//	//objShader->useProgram();
	//	//objShader->setMat4("projection", this->projection);
	//}
	//
	//// === VIEW RELATED ============================
	//GraphicObject& setView(glm::mat4 view ) {
	//	this->view = view;
	//	objShader->useProgram();
	//	objShader->setMat4("u_view", this->view);
	//	return *this;
	//}
	//
	//
	//void translateCam(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
	//	// calc. the model matrix for each object and pass it to shader before drawing
	//	this->view = glm::translate(this->view, position);
	//	this->setView(this->view);
	//}
	//
	//// === MODEL RELATED ===========================
	//GraphicObject& setModel(glm::mat4 model) {
	//	this->model = model;
	//	objShader->useProgram();
	//	objShader->setMat4("u_model", this->model);
	//	return *this;
	//}


	// === MVP RELATED =========================

	void initMVP(glm::mat4 view = glm::mat4(0), glm::mat4 proj = glm::mat4(0)) {
		this->model = glm::mat4(1.0f);
		this->view = glm::mat4(1.0f);
		this->projection = glm::mat4(1.0f);


		// Should the view be set;
		if (view != glm::mat4(0))	this->view = view;
		else						this->view = glm::translate(this->view, glm::vec3(0.0f, 0.0f, -3.0f));

		// should the projection be set
		if (proj != glm::mat4(0))	this->projection = proj;
		else						this->projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
	
	}


	GraphicObject& setMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

		this->model = model;
		this->view = view;
		this->projection = projection;

		this->MVP = this->projection * this->view * this->model;

		bindVertex();
		objShader->useProgram();
		objShader->setMat4("u_MVP", this->MVP);

		return *this;
	}



	glm::mat4 getModel() const { return this->model; }
	glm::mat4 getView() const { return this->view;  }
	glm::mat4 getProjection() const { return this->projection; }

	// === TRANSFORMATIONS RELATED =========================

	void translate(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
		// calc. the model matrix for each object and pass it to shader before drawing

		this->model = glm::translate(this->model, position);
		this->setMVP(this->model, this->view, this->projection);
	}

	void rotate(const float angle = 0.0f, glm::vec3 rotateAround = glm::vec3(0.0f, 0.0f, 1.0f)) {
	
		this->model = glm::rotate(this->model, glm::radians(angle), rotateAround);
		this->setMVP(this->model, this->view, this->projection);
		
	}

	void scale(float x, float y, float z) {
		this->model = glm::scale(this->model, glm::vec3(x, y, z));
		this->setMVP(this->model, this->view, this->projection);
	}

	void scale(float value) {
		this->scale(value, value, value);
	}

	void resetModel() {
		this->model = glm::mat4(1.0f);
	}


	void bindVertex() const {
		glBindVertexArray(VAO);
	}

	void unbindVertex()const {
		glBindVertexArray(0);
	}


	void draw(){

		// render boxes
		//this->bindVertex();
		if (hasIBO) glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
		else		glDrawArrays(GL_TRIANGLES, 0, verticesInfo.size());
		//this->unbindVertex();

	}



	~GraphicObject() {
		delete objShader;
		delete tex1;
	}

};


#endif # GRAPHICOBJECT_H