#pragma once


#include "GraphicObject.h"
struct MeshData {
	vector<VertexInfo> mesh;
	vector<unsigned int> indices;
};

// Cube Mesh WITHOUT indices
vector<VertexInfo> GetCubeMesh() {

	vector<VertexInfo> cubeVertices;
	VertexInfo::attribComponentCount = { 3, 2 };
	cubeVertices.push_back({ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f });
	cubeVertices.push_back({ 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, });

	cubeVertices.push_back({ -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, });

	cubeVertices.push_back({ -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, });
	cubeVertices.push_back({ -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, });

	cubeVertices.push_back({ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, });

	cubeVertices.push_back({ -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, });
	cubeVertices.push_back({ -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, });

	cubeVertices.push_back({ -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, });
	cubeVertices.push_back({ -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, });
	cubeVertices.push_back({ -0.5f,  0.5f, -0.5f,  0.0f, 1.0f });

	return cubeVertices;
}


// Rectangle mesh with indices
MeshData GetRectangleMesh() {
	vector<VertexInfo> rectVertices;
	VertexInfo::attribComponentCount = { 3,  2 };
	rectVertices.push_back({ 0.5f,  0.5f, 0.0f,   1.0f, 1.0f });
	rectVertices.push_back({ 0.5f, -0.5f, 0.0f,   1.0f, 0.0f });
	rectVertices.push_back({ -0.5f, -0.5f, 0.0f,  0.0f, 0.0f });
	rectVertices.push_back({ -0.5f,  0.5f, 0.0f,  0.0f, 1.0f });

	vector<unsigned int>indices = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
	};

	return { rectVertices, indices };
}