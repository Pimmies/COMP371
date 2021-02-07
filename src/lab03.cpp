//
// COMP 371 Labs Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//

#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

	//declare our functions
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);
	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
	void drawCamil(int shaderProgram, glm::vec3 translationMatrix);
	void drawJulie(int shaderProgram, glm::vec3 translationMatrix);
    void drawClaudia(int shaderProgram, glm::vec3 translationMatrix);
    void drawCharles(int shaderProgram, glm::vec3 translationMatrix);
    void drawJ(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
	void drawP(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
	void draw4(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
	void draw5(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
    void drawC(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
    void drawG(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
    void drawR(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
    void draw2(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
    void draw9(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
	void drawB(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
	void draw1(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
    void draw3(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix);
	
	// screen size settings
	const unsigned int SCR_WIDTH = 1024;
	const unsigned int SCR_HEIGHT = 768;

	// camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//user input settings
	//panning (left right) and tilting (up down), zoom
	bool enablePan = false; //initially false until right click is pressed
	bool enableTilt = false; //initially false until middle click is pressed
	bool enableZoom = false; //initially false until the left click is pressed
	bool firstMouse = true;
	float pan = -90.0f;	// pan is initialized to -90.0 degrees since a pan of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float tilt = 0.0f;
	float lastX = SCR_WIDTH / 2.0;  //the mouse cursor is initially in the middle of the screen
	float lastY = SCR_HEIGHT / 2.0;
	float fieldOfView = 45.0f; //perspective viewing angle. Will change when we zoom in and out

	//delta time between frames
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame


	//HIERARCHY EXPLAINED
	//sets perspective           //sets camera view          //transforms a group of letters representing a student      //transforms one individual letter         //transforms one individual cube
	//projection     *           view             *           studentMatrix                *                             letterMatrix                       *       transform
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 worldMatrix;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * worldMatrix * vec4(aPos, 1.0);\n"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";

	int main()
	{
		//INITIALIZE GLFW
		glfwInit();
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetCursorPosCallback(window, cursor_position_callback); //call mouse_callback automatically every time the mouse moves
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //call framebuffer_size_callback automatically every time the window is resized in order to adjust the view port

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to create GLEW" << std::endl;
			glfwTerminate();
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
		glEnable(GL_DEPTH_TEST);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE); //sticky mouse button enabled so that press and release are captured
        
		//VERTICES FOR A CUBE
		float vertices[] = {
			//position
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		//SETTING VERTEX ATTRIBUTES
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO); //stores VBO
		glGenBuffers(1, &VBO); //stores vertices

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
		glEnableVertexAttribArray(0);

		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));  //tells gpu how to interpret texture
		//glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glm::mat4 view; //updated in render loop
		glm::mat4 projection; //updated in render loop

		//get uniform location for view and projection
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");


		//RENDER LOOP
		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); //the view is updated every frame because cameraPos is dynamically changed with keyboard input and cameraFront is dynamically changed with cursor movement
			projection = glm::perspective(glm::radians(fieldOfView), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); //the perspective is updated every frame because the fieldOfView is dynamically changed by zooming

			//pass updated settings to the shader
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			drawJulie(shaderProgram, glm::vec3(0.0f, 0.0f, 0.0f));
			/*drawClaudia(shaderProgram, glm::vec3(0.0f, 5.0f, 0.0f));
			drawCamil(shaderProgram, glm::vec3(0.0f, 10.0f, 0.0f));
			drawCharles(shaderProgram, glm::vec3(0.0f, -5.0f, 0.0f));*/
            
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		//de-allocate all resources
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);

		glfwTerminate();
		return 0;
	}

	//translationMatrix: this matrix gets applied to the studentMatrix. This in turn allows to move the group of letters around
	void drawJulie(int shaderProgram, glm::vec3 translationMatrix)
	{
		glm::mat4 studentMatrix = glm::mat4(1.0f); //the studentMatrix is originally the identity matrix. That's why we apply transformations onto it
		studentMatrix = glm::translate(studentMatrix, translationMatrix); //translationMatrix is applied to the studentMatrix

		//draw letters
		drawJ(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix);
		drawP(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f), studentMatrix);
		draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
		draw5(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
	}

	//translationMatrix: gets applied to the studentMatrix. Allows to move the group of letters around
    void drawCharles(int shaderProgram, glm::vec3 translationMatrix){

        glm::mat4 studentMatrix = glm::mat4(1.0f); //the studentMatrix is originally the identity matrix. That's why we apply transformations onto it
        studentMatrix = glm::translate(studentMatrix, translationMatrix); //translationMatrix is applied to the studentMatrix

        //draw letters
        drawC(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix); //check this function for detailed explanation
        drawR(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f), studentMatrix);
        draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        draw3(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
        
    }

	//translationMatrix: gets applied to the studentMatrix. Allows to move the group of letters around
	void drawClaudia(int shaderProgram, glm::vec3 translationMatrix) {
        
		glm::mat4 studentMatrix = glm::mat4(1.0f); //the studentMatrix is originally the identity matrix. That's why we apply transformations onto it
        studentMatrix = glm::translate(studentMatrix, translationMatrix); //translationMatrix is applied to the studentMatrix
        
        //draw letters
        drawC(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix);
        drawG(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f), studentMatrix);
        draw2(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        draw9(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
	}

	//translationMatrix: gets applied to the studentMatrix. Allows to move the group of letters around
	void drawMax(int shaderProgram, glm::vec3 translationMatrix)
	{}

	//translationMatrix: gets applied to the studentMatrix. Allows to move the group of letters around
	void drawCamil(int shaderProgram, glm::vec3 translationMatrix)
	{
		glm::mat4 studentMatrix = glm::mat4(1.0f); //the studentMatrix is originally the identity matrix. That's why we apply transformations onto it
		studentMatrix = glm::translate(studentMatrix, translationMatrix); //translationMatrix is applied to the studentMatrix

		//draw letters
		drawC(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix); //check this function for detailed explanation
		drawB(shaderProgram, glm::vec3(-2.5f, 0.0f, 0.0f), studentMatrix);
		draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
		draw1(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
	}

	//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
	void drawB(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
		glm::mat4 letterMatrix = glm::mat4(1.0f); //the letterMatrix is originally the identity matrix.
		letterMatrix = glm::translate(letterMatrix, translationMatrix);

		//1st cube: long one
		glm::mat4 transform = glm::mat4(1.0f); //starts as a clean identity matrix
		transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 0.5f)); //scale it

		//update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

		glDrawArrays(GL_TRIANGLES, 0, 36); //draw cube

		//2nd cube: bottom base
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.8f, -1.25f, 0.0f)); //third translate
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
		transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36); //draw cube

		//3rd cube: top part
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.6f, 1.25f, 0.0f)); //third translate
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
		transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//4th cube: middle part
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.8f, 0.01f, 0.0f)); //third translate
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
		transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//5th cube: close top loop
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(1.0f, 0.8f, 0.0f)); //third translate
		transform = glm::scale(transform, glm::vec3(0.5f, 1.4f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//6th cube: close bottom loop
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(1.8f, -0.62f, 0.0f)); //third translate
		transform = glm::scale(transform, glm::vec3(0.5f, 1.76f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
	void drawJ(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
		glm::mat4 letterMatrix = glm::mat4(1.0f); //the letterMatrix is originally the identity matrix. That's why we apply transformations onto it
		letterMatrix = glm::translate(letterMatrix, translationMatrix);

		//1st cube
		//the transform matrix transforms an individual cube
		glm::mat4 transform = glm::mat4(1.0f); //starts as a clean identity matrix
		transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f)); //scale it

		//declare worldMatrix, get location and update
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

		glDrawArrays(GL_TRIANGLES, 0, 36); //now we can draw that 1st cube!

		//2nd cube
		transform = glm::mat4(1.0f); //important! transform matrix need to be set back to a clean state (identity matrix) because we are transforming a new cube!
		transform = glm::translate(transform, glm::vec3(-0.8f, -1.25f, 0.0f)); //third translate
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36); // now we draw!

		//3rd cube
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-1.3f, -0.75f, 0.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//4th cube
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
	void drawP(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
		glm::mat4 letterMatrix = glm::mat4(1.0f);
		letterMatrix = glm::translate(letterMatrix, translationMatrix);

		//1st cube
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

		//declare and update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//2
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.8f, 1.25f, 0.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//3
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.8f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//4
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(1.3f, 0.7f, 0.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
	void draw1(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
		glm::mat4 letterMatrix = glm::mat4(1.0f); //the letterMatrix is originally the identity matrix.
		letterMatrix = glm::translate(letterMatrix, translationMatrix);

		//1st cube: long vertical
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 0.5f));

		//update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

		glDrawArrays(GL_TRIANGLES, 0, 36); //draw cube

		//2nd cube: base
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f)); //second translate
		transform = glm::scale(transform, glm::vec3(1.75f, 0.5f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//3rd cube: first part of hanging part
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.30f, 1.25f, 0.0f)); //second translate
		transform = glm::scale(transform, glm::vec3(0.75f, 0.5f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//4th cube: rotated hanging part
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.82f, 1.06f, 0.0f)); //third translate
		transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //second rotate
		transform = glm::scale(transform, glm::vec3(0.8f, 0.4f, 0.5f));  //first scale

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
	void draw4(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
		glm::mat4 letterMatrix = glm::mat4(1.0f);
		letterMatrix = glm::translate(letterMatrix, translationMatrix);

		//1st cube
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

		//declare and update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//2
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.8f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//3
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.7f, 0.7f, 0.0f));
		transform = glm::rotate(transform, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.8f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//translationMatrix: this matrix gets applied to the letterMatrix. This in turn allows to move the group of cubes (a letter) around
	void draw5(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
		glm::mat4 letterMatrix = glm::mat4(1.0f);
		letterMatrix = glm::translate(letterMatrix, translationMatrix);

		//1st cube
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//declare and update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//2
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//3
		transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//4
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.75f, 0.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//5
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.75f, 0.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

    void drawC(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
{
    glm::mat4 letterMatrix = glm::mat4(1.0f);
    letterMatrix = glm::translate(letterMatrix, translationMatrix);

    //1st cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	//update uniform location world matrix
	glm::mat4 worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	//update uniform location world matrix
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 2.5f, 1.0f));

	//update uniform location world matrix
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

    void drawG(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
{
    glm::mat4 letterMatrix = glm::mat4(1.0f);
    letterMatrix = glm::translate(letterMatrix, translationMatrix);

    //1st cube - bottom (horizontal)
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.75f, 1.0f));

	//update uniform location world matrix
	glm::mat4 worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //2 - top (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.75f, 1.0f));

	//update uniform location world matrix
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //3 - middle (horizontal)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 1.0f));

	//update uniform location world matrix
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //4 - right (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.75f, -0.75f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

	//update uniform location world matrix
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //5 - left (vertical)
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(-0.62f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 2.0f, 1.0f));

	//update uniform location world matrix
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = studentMatrix * letterMatrix * transform;

	worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
	
	void draw2(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
        glm::mat4 letterMatrix = glm::mat4(1.0f);
        letterMatrix = glm::translate(letterMatrix, translationMatrix);

        unsigned int letterMatrixLoc = glGetUniformLocation(shaderProgram, "letterMatrix");
        glUniformMatrix4fv(letterMatrixLoc, 1, GL_FALSE, glm::value_ptr(letterMatrix));

        //1st cube - bottom (horizontal)
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //2 - top (horizontal)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //3 middle (horizontal)
        transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //4 - right (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(-0.5f, -0.75f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //5 - left (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, 0.75f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void draw9(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
    {
        glm::mat4 letterMatrix = glm::mat4(1.0f);
        letterMatrix = glm::translate(letterMatrix, translationMatrix);

        //1 - top (horizontal)
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //2 middle (horizontal)
        transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //3 - right (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //4 - left (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.75f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    void draw3(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix)
	{
        
        glm::mat4 letterMatrix = glm::mat4(1.0f);
        letterMatrix = glm::translate(letterMatrix, translationMatrix);

        //1 - top (horizontal)
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //2 middle (horizontal)
        transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //3 - lower (horizontal)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, -1.25f, 0.0f));
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //4 - right (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));
        
		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        

        /*glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawArrays(GL_TRIANGLES, 0, 36);*/
    }

    void drawR(int shaderProgram, glm::vec3 translationMatrix, glm::mat4 studentMatrix){
        
        glm::mat4 letterMatrix = glm::mat4(1.0f);
        letterMatrix = glm::translate(letterMatrix, translationMatrix);
        
        //1 - top (horizontal)
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, 1.25f, 0.0f));
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //2 middle (horizontal)
        transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));

		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //3 - left (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 3.0f, 1.0f));
        
		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //4 - right (vertical)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));
        
		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //5 - right (diagonal)
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.25f, -0.75f, 0.0f));
        transform = glm::rotate(transform, glm::radians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 1.5f, 1.0f));
        
        
		//update uniform location world matrix
		worldMatrix = glm::mat4(1.0f);
		worldMatrix = studentMatrix * letterMatrix * transform;

		worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrixLoc");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
	
	//when the window size is changed, this function is called
	void framebuffer_size_callback(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	//when the mouse buttons are pressed, this function is called
	//documentation: https://www.glfw.org/docs/3.3/input_guide.html
	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) //enable pan when pressed
		{
			enablePan = true;
		}

		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) //disable pan when released
		{
			enablePan = false;
		}

		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) //enable tilt when pressed
		{
			enableTilt = true;
		}

		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) //disable tilt when released
		{
			enableTilt = false;
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) //enable zoom when pressed
		{
			enableZoom = true;
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) //disable zoom when released
		{
			enableZoom = false;
		}
	}

	//when the cursor moves, this function is called
	//documentation: https://www.glfw.org/docs/3.3/input_guide.html
	//source: https://learnopengl.com/Getting-started/Camera
	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		float sensitivity = 0.2f;

		//calculate the difference between the mouse position in the last and current frame
		//NOTE!!!: We are always calculating the offset, even when pan and tilt aren't enabled. This prevents the camera from jumping if pan or tilt is re-enabled after moving the cursor
		float xoffset = xpos - lastX;
		lastX = xpos;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastY = ypos;

		if (enablePan == true) //enablePan becomes true in the mouse_button_callback() function when the right click is pressed. False when released
		{
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			xoffset = xoffset * sensitivity;

			pan = pan + xoffset;

			//update the camera front vector based on our mouse movement
			glm::vec3 front;
			front.x = cos(glm::radians(pan)) * cos(glm::radians(tilt));
			front.y = sin(glm::radians(tilt));
			front.z = sin(glm::radians(pan)) * cos(glm::radians(tilt));
			cameraFront = glm::normalize(front);
		}

		if (enableTilt == true) //enableTilt becomes true in the mouse_button_callback() function when the middle click is pressed. False when released
		{
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			tilt = tilt + yoffset;

			// make sure that when tilt is out of bounds, screen doesn't get flipped
			if (tilt > 89.0f)
				tilt = 89.0f;
			if (tilt < -89.0f)
				tilt = -89.0f;

			//update the camera front vector based on our mouse movement
			glm::vec3 front;
			front.x = cos(glm::radians(pan)) * cos(glm::radians(tilt));
			front.y = sin(glm::radians(tilt));
			front.z = sin(glm::radians(pan)) * cos(glm::radians(tilt));
			cameraFront = glm::normalize(front);
		}

		if (enableZoom == true) //enableZoom becomes true in the mouse_button_callback() function when the left click is pressed. False when released
		{
			fieldOfView = fieldOfView - (float)yoffset;
			//constraints
			if (fieldOfView < 1.0f)
				fieldOfView = 1.0f;
			if (fieldOfView > 45.0f)
				fieldOfView = 45.0f;
		}
	}

	//process keyboard input
	//source: https://learnopengl.com/Getting-started/Camera
	void processInput(GLFWwindow * window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		//walk around
		float cameraSpeed = 2.5 * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			cameraPos = cameraPos + cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			cameraPos = cameraPos - cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			cameraPos = cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			cameraPos = cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
