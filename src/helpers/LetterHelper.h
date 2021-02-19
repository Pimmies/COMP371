//
// Created by Max Sun on 2/7/21.
//

#ifndef LAB_3_LETTERHELPER_H
#define LAB_3_LETTERHELPER_H

#include <stdio.h>
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
// cross-platform interface for creating a graphical context,

class LetterHelper{
public:
    static void drawJ(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawP(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void draw4(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void draw5(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawC(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawG(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawR(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void draw2(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void draw9(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawB(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
	static void drawSphere(int shaderProgram, glm::mat4 matrixToApply, int VAO_circle, int VAO_cube);
	static void drawBLast(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix, int VAO_circle, int VAO_cube);
	static void drawOLast(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix, int VAO_circle, int VAO_cube);
	static void drawULast(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix, int VAO_circle, int VAO_cube);
	static void drawZLast(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix, int VAO_circle, int VAO_cube);
	static void drawILast(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix, int VAO_circle, int VAO_cube);
	static void drawDLast(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix, int VAO_circle, int VAO_cube);
    static void draw1(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void draw3(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawN(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
    static void drawS(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix);
};

#endif //LAB_3_LETTERHELPER_H
