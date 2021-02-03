#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void drawJulie(int shaderProgram, glm::vec3 translationMatrix);
void drawJ(int shaderProgram, glm::vec3 letterMatrix);
void drawP(int shaderProgram, glm::vec3 letterMatrix);
void draw4(int shaderProgram, glm::vec3 letterMatrix);
void draw5(int shaderProgram, glm::vec3 letterMatrix);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 transform;\n"
"uniform mat4 letterMatrix;\n"
"uniform mat4 studentMatrix;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * studentMatrix * letterMatrix * transform * vec4(aPos, 1.0);\n"
"	TexCoord = aTexCoord;\n"	
"}";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"   FragColor = texture(ourTexture, TexCoord);\n"
"}";

int main() 
{
	//INITIALIZE GLFW
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //call this function automatically every time the window is resized in order to adjust the view port

	//INITIALIZE GLAD's function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//compiling a vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//compiling a fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//creating a shader program object to link and use the compiled shaders
	int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader); //no longer need them once they've been linked
	glDeleteShader(fragmentShader);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	//VERTICES FOR A CUBE + TEXTURE
	float vertices[] = {
		//position             //texture
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//SETTING VERTEX ATTRIBUTES
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); //stores VBO
	glGenBuffers(1, &VBO); //stores vertices
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));  //tells gpu how to interpret texture
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	// load and create a texture 
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); //safe because it was assigned to GL_TEXTURE_2D

	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//HIERARCHY EXPLAINED
		//sets perspective           //sets camera view          //transforms a group of letters representing a student      //transforms one individual letter         //transforms one individual cube
		//projection     *           view             *           studentMatrix                *                             letterMatrix                       *       transform

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -30.0f)); //sets our view by moving the world back along the z-axis
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		//get uniform location for view and projection
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

		//update view and location uniforms with our latest settings(???)
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		drawJulie(shaderProgram, glm::vec3(0.0f, -8.0f, 0.0f)); //right now I'm pushing Julie down by 8 units
		//drawCharles...
		//draw ...

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	
	glfwTerminate();
	return 0;
}

//draws Julie
//shaderProgram: our shader program (composed of the vertex and fragment shaders)
//translationMatrix: this matrix gets applied to the studentMatrix. This in turn allows to move the group of letters around
void drawJulie(int shaderProgram, glm::vec3 translationMatrix)
{
	glm::mat4 studentMatrix = glm::mat4(1.0f); //the studentMatrix is originally the identity matrix. That's why we apply transformations onto it
	studentMatrix = glm::translate(studentMatrix, translationMatrix); //translationMatrix is applied to the studentMatrix
	
	//get uniform location of the studentMatrix
	unsigned int studentMatrixLoc = glGetUniformLocation(shaderProgram, "studentMatrix");

	//update the studentMatrix uniform to our latest settings (set above)
	glUniformMatrix4fv(studentMatrixLoc, 1, GL_FALSE, glm::value_ptr(studentMatrix));  //one student matrix applied to every letter so that the letters move as a group

	//draw letters
	drawJ(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f)); //check this function for detailed explanation
	drawP(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f));
	draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f));
	draw5(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f));
}

void drawCharles(int shaderProgram, glm::vec3 translationMatrix)
{}

void drawClaudia(int shaderProgram, glm::vec3 translationMatrix)
{}

void drawMax(int shaderProgram, glm::vec3 translationMatrix)
{}

void drawCamil(int shaderProgram, glm::vec3 translationMatrix)
{}

//draws a J
//shaderProgram: our shader program (composed of the vertex and fragment shaders)
//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
void drawJ(int shaderProgram, glm::vec3 translationMatrix)
{
	glm::mat4 letterMatrix = glm::mat4(1.0f); //the letterMatrix is originally the identity matrix. That's why we apply transformations onto it
	letterMatrix = glm::translate(letterMatrix, translationMatrix);

	unsigned int letterMatrixLoc = glGetUniformLocation(shaderProgram, "letterMatrix"); //get uniform location
	glUniformMatrix4fv(letterMatrixLoc, 1, GL_FALSE, glm::value_ptr(letterMatrix)); //update the uniform with our latest settings

	//1st cube
	//the transform matrix transforms an individual cube
	glm::mat4 transform = glm::mat4(1.0f); //starts as a clean identity matrix
	transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f)); //scale it

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform"); //get uniform location
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));  //update the uniform with our latest settings
	
	glDrawArrays(GL_TRIANGLES, 0, 36); //now we can draw that 1st cube!

	//2nd cube
	transform = glm::mat4(1.0f); //important! transform matrix need to be set back to a clean state (identity matrix) because we are transforming a new cube!
	transform = glm::translate(transform, glm::vec3(-0.8f, -1.25f, 0.0f)); //third translate
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));  //first scale

	//no need to "get the uniform location" because we already got it earlier
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform)); //however, we still need to update it to our latest settings
	glDrawArrays(GL_TRIANGLES, 0, 36); // now we draw!

	//etc...

	//3rd cube
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-1.3f, -0.75f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//4th cube
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//draws a P
//shaderProgram: our shader program (composed of the vertex and fragment shaders)
//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
void drawP(int shaderProgram, glm::vec3 translationMatrix)
{
	glm::mat4 letterMatrix = glm::mat4(1.0f);
	letterMatrix = glm::translate(letterMatrix, translationMatrix);

	unsigned int letterMatrixLoc = glGetUniformLocation(shaderProgram, "letterMatrix");
	glUniformMatrix4fv(letterMatrixLoc, 1, GL_FALSE, glm::value_ptr(letterMatrix));

	//1st cube
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//2
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.8f, 1.25f, 0.0f));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//3
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.8f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//4
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(1.3f, 0.7f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//draws a 4
//shaderProgram: our shader program (composed of the vertex and fragment shaders)
//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
void draw4(int shaderProgram, glm::vec3 translationMatrix)
{
	glm::mat4 letterMatrix = glm::mat4(1.0f);
	letterMatrix = glm::translate(letterMatrix, translationMatrix);

	unsigned int letterMatrixLoc = glGetUniformLocation(shaderProgram, "letterMatrix");
	glUniformMatrix4fv(letterMatrixLoc, 1, GL_FALSE, glm::value_ptr(letterMatrix));

	//1st cube
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));
	
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//2
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-0.8f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//3
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-0.7f, 0.7f, 0.0f));
	transform = glm::rotate(transform, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.8f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//draws a 5
//shaderProgram: our shader program (composed of the vertex and fragment shaders)
//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
void draw5(int shaderProgram, glm::vec3 translationMatrix)
{
	glm::mat4 letterMatrix = glm::mat4(1.0f);
	letterMatrix = glm::translate(letterMatrix, translationMatrix);

	unsigned int letterMatrixLoc = glGetUniformLocation(shaderProgram, "letterMatrix");
	glUniformMatrix4fv(letterMatrixLoc, 1, GL_FALSE, glm::value_ptr(letterMatrix));
	
	//1st cube
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//2
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//3
	transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//4
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.5f, -0.75f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//5
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-0.5f, 0.75f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);  //window closes when escape is pressed
}

