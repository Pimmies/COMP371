//
//  letterHelper.cpp
//  Lab_3
//
//  Created by Max Sun on 2/7/21.
//

#include "LetterHelper.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void LetterHelper::drawB(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube: long one
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 0.5f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36); //draw cube

    //2nd cube: bottom base
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.8f, -1.25f, 0.0f)); //third translate
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
    transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 0.5f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36); //draw cube

    //3rd cube: top part
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.6f, 1.25f, 0.0f)); //third translate
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
    transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 0.5f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4th cube: middle part
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.8f, 0.01f, 0.0f)); //third translate
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
    transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 0.5f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //5th cube: close top loop
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.0f, 0.8f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.4f, 0.5f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //6th cube: close bottom loop
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.8f, -0.62f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.76f, 0.5f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawJ(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube
    //the transform matrix transforms an individual cube
    glm::mat4 transform = glm::mat4(1.0f); 
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //declare modelMatrix, get location and update
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2nd cube
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.8f, -1.25f, 0.0f)); //third translate
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3rd cube
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-1.3f, -0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4th cube
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawP(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //declare and update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.8f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.8f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.3f, 0.7f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::draw1(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube: long vertical
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 0.5f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36); //draw cube

    //2nd cube: base
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f)); //second translate
    transform = glm::scale(transform, glm::vec3(1.75f, 0.5f, 0.5f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3rd cube: first part of hanging part
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.30f, 1.25f, 0.0f)); //second translate
    transform = glm::scale(transform, glm::vec3(0.75f, 0.5f, 0.5f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4th cube: rotated hanging part
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.82f, 1.06f, 0.0f)); //third translate
    transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
    transform = glm::scale(transform, glm::vec3(0.8f, 0.4f, 0.5f));  //first scale

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::draw4(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //declare and update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.8f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.7f, 0.7f, 0.0f));
    transform = glm::rotate(transform, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.8f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::draw5(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //declare and update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3
    transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //5
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawC(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
//1st cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

//update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

//2
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

//update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

//3
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 2.5f, 1.0f));

//update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawG(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{

//1st cube - bottom (horizontal)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.75f, 1.0f));

//update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

//2 - top (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.75f, 1.0f));

//update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

//3 - middle (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 1.0f));

//update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

//4 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.75f, -0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

//update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

//5 - left (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.62f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 1.0f));

//update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::draw2(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube - bottom (horizontal)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2 - top (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3 middle (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, -0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //5 - left (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::draw9(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1 - top (horizontal)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2 middle (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4 - left (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawN(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1 - middle (slash)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.3f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(24.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 3.1f, 1.0f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4 - left (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-1.0f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawS(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1st cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 0.7f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.3f, 1.0f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //top-hoizontal
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.7f, 1.3f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.3f, 1.75f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //middle-hoizontal
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.7f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.3f, 1.75f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //bottom-hoizontal
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.7f, -1.3f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.3f, 1.75f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(1.4f, -0.7f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.1f, 1.0f));

    //update uniform location model matrix
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::draw3(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix)
{
    //1 - top (horizontal)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2 middle (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3 - lower (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LetterHelper::drawR(int shaderProgram, glm::mat4 letterMatrix, glm::mat4 studentMatrix){
    //1 - top (horizontal)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    unsigned int modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2 middle (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3 - left (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //5 - right (diagonal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.25f, -0.75f, 0.0f));
    transform = glm::rotate(transform, glm::radians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));


    //update uniform location model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = studentMatrix * letterMatrix * transform;

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
