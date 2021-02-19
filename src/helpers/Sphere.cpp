#include "Sphere.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

Sphere::Sphere()
{
	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
	shaderProgram = 0;

	lats = 40;
	longs = 40;
}

Sphere::~Sphere()
{

}

void Sphere::init(int shaderProg)
{
	int i, j;
	std::vector<float> vertices;
	std::vector<GLuint> indices;
	int indicator = 0;
	for (i = 0; i <= lats; i++) {
		double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		for (j = 0; j <= longs; j++) {
			double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			vertices.push_back(x * zr0);
			vertices.push_back(y * zr0);
			vertices.push_back(z0);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			indices.push_back(indicator);
			indicator++;

			vertices.push_back(x * zr1);
			vertices.push_back(y * zr1);
			vertices.push_back(z1);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
			indices.push_back(indicator);
			indicator++;
		}
		indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
	}

	// 创建并绑定环境
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	int n = vertices.size();

	float* verticesArray = new float[n];
	for (int i = 0; i < n; i++) {
		verticesArray[i] = vertices[i];
	}

	glGenBuffers(1, &m_vboVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), verticesArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   //interpret the colours
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*glGenBuffers(1, &m_vboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);*/

	numsToDraw = indices.size();

	isInited = true;
	shaderProgram = shaderProg;
}

void Sphere::cleanup()
{
	if (!isInited) {
		return;
	}
	if (m_vboVertex) {
		glDeleteBuffers(1, &m_vboVertex);
	}
	if (m_vboIndex) {
		glDeleteBuffers(1, &m_vboIndex);
	}
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
}

void Sphere::draw()
{
	if (!isInited) {
		std::cout << "please call init() before draw()" << std::endl;
	}

	// draw sphere
	glBindVertexArray(m_vao);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glDrawElements(GL_QUAD_STRIP, numsToDraw, GL_UNSIGNED_INT, NULL);
}
