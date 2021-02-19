#pragma once
//Thanks to https://gist.github.com/zwzmzd/0195733fa1210346b00d for code 
#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glew.h>

class Sphere
{
public:
	Sphere();
	~Sphere();
	void init(int shaderProg);
	void cleanup();
	void draw();
	int lats, longs, shaderProgram;
	bool isInited;
	GLuint m_vao, m_vboVertex, m_vboIndex;
	int numsToDraw;
};

#endif // SPHERE_H