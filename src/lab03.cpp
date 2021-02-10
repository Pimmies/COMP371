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
#include "helpers/LetterHelper.h"

//declare our functions
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);
	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void scaleModelUp();
	void scaleModelDown();
	void moveModelLeft();
	void moveModelRight();
	void moveModelUp();
	void moveModelDown();
	void rotateModelLeft();
	void rotateModelRight();
	void processPolygonMode(GLFWwindow* window);
	void drawCamil(int shaderProgram, glm::mat4 studentMatrix);
	void drawJulie(int shaderProgram, glm::mat4 studentMatrix);
    void drawClaudia(int shaderProgram, glm::mat4 studentMatrix);
    void drawCharles(int shaderProgram, glm::mat4 studentMatrix);
	void drawMax(int shaderProgram, glm::mat4 studentMatrix);
    void drawLines(int shaderProgram);
	void drawCircle(int shaderProgram);
    void drawGrid(int shaderProgram, glm::vec3 translationMatrix);

// screen size settings
	const unsigned int SCR_WIDTH = 1024;
	const unsigned int SCR_HEIGHT = 768;

	// camera
//	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// camera position to see axis (testing)
    glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 5.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -3.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//selected student
	//0:Julie 1:Claudia 2:Camil 3:Charles 4:Max
	int currentStudent = -1;
	glm::mat4 studentMatrixArray[5];
	
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
		"layout (location = 1) in vec3 aColor;\n"
		"uniform mat4 worldMatrix;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * worldMatrix * vec4(aPos, 1.0);\n"
		"	ourColor = aColor;\n"
		"}";

	const char* fragmentShaderSource = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0);\n"
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
		glfwSetKeyCallback(window, key_callback);
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
			//position				//colour
			-0.5f, -0.5f, -0.5f, 0.796f, 0.282f, 0.282f, //light red
			 0.5f, -0.5f, -0.5f, 0.796f, 0.282f, 0.282f,
			 0.5f,  0.5f, -0.5f, 0.796f, 0.282f, 0.282f,
			 0.5f,  0.5f, -0.5f, 0.796f, 0.282f, 0.282f,
			-0.5f,  0.5f, -0.5f, 0.796f, 0.282f, 0.282f,
			-0.5f, -0.5f, -0.5f, 0.796f, 0.282f, 0.282f,

			-0.5f, -0.5f,  0.5f, 0.796f, 0.282f, 0.780f, //light pinkish-purple
			 0.5f, -0.5f,  0.5f, 0.796f, 0.282f, 0.780f,
			 0.5f,  0.5f,  0.5f, 0.796f, 0.282f, 0.780f,
			 0.5f,  0.5f,  0.5f, 0.796f, 0.282f, 0.780f,
			-0.5f,  0.5f,  0.5f, 0.796f, 0.282f, 0.780f,
			-0.5f, -0.5f,  0.5f, 0.796f, 0.282f, 0.780f,

			-0.5f,  0.5f,  0.5f, 0.282f, 0.654f, 0.796f,  //light blue
			-0.5f,  0.5f, -0.5f, 0.282f, 0.654f, 0.796f,
			-0.5f, -0.5f, -0.5f, 0.282f, 0.654f, 0.796f,
			-0.5f, -0.5f, -0.5f, 0.282f, 0.654f, 0.796f,
			-0.5f, -0.5f,  0.5f, 0.282f, 0.654f, 0.796f,
			-0.5f,  0.5f,  0.5f, 0.282f, 0.654f, 0.796f,

			 0.5f,  0.5f,  0.5f, 0.282f, 0.796f, 0.498f,  //light green
			 0.5f,  0.5f, -0.5f, 0.282f, 0.796f, 0.498f,
			 0.5f, -0.5f, -0.5f, 0.282f, 0.796f, 0.498f,
			 0.5f, -0.5f, -0.5f, 0.282f, 0.796f, 0.498f,
			 0.5f, -0.5f,  0.5f, 0.282f, 0.796f, 0.498f,
			 0.5f,  0.5f,  0.5f, 0.282f, 0.796f, 0.498f,

			-0.5f, -0.5f, -0.5f, 0.882f, 0.878f, 0.419f, //light yellow
			 0.5f, -0.5f, -0.5f, 0.882f, 0.878f, 0.419f,
			 0.5f, -0.5f,  0.5f, 0.882f, 0.878f, 0.419f,
			 0.5f, -0.5f,  0.5f, 0.882f, 0.878f, 0.419f,
			-0.5f, -0.5f,  0.5f, 0.882f, 0.878f, 0.419f,
			-0.5f, -0.5f, -0.5f, 0.882f, 0.878f, 0.419f,

			-0.5f,  0.5f, -0.5f, 0.980f, 0.529f, 0.160f,  //orange
			 0.5f,  0.5f, -0.5f, 0.980f, 0.529f, 0.160f,
			 0.5f,  0.5f,  0.5f, 0.980f, 0.529f, 0.160f,
			 0.5f,  0.5f,  0.5f, 0.980f, 0.529f, 0.160f,
			-0.5f,  0.5f,  0.5f, 0.980f, 0.529f, 0.160f,
			-0.5f,  0.5f, -0.5f, 0.980f, 0.529f, 0.160f,
		};
        
		float axisVertices[] = {
			//coordinate		colours
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			7.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 7.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 1.0f,
		};

		//VERTICES FOR A CIRCLE
		//helper source: https://stackoverflow.com/questions/32443776/drawing-a-circle-with-opengl
		float x;
		float y;
		float z = 0.0f;
		float angle = 0.0f;
		float radius = 15.0f;
		int currentIndex = 0;
		int numPoints = 30;
		float circleVertices[90];  //numPoints * 3

		for (int i = 0; i < numPoints; i++)
		{
			x = (float)(radius * cos(glm::radians(angle)));
			y = (float)(radius * sin(glm::radians(angle)));

			circleVertices[i * 3] = x;
			circleVertices[i * 3 + 1] = y;
			circleVertices[i * 3 + 2] = z;

			angle = (float)(angle + (360.0f / numPoints));
		}
        
        float gridVertices[] = {
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
        };

        //SETTING VERTEX ATTRIBUTES
        unsigned int VAO_cube, VBO_cube, VAO_axis, VBO_axis, VAO_circle, VBO_cirle, VAO_grid, VBO_grid;
		glGenVertexArrays(1, &VAO_cube);
		glGenBuffers(1, &VBO_cube); //stores vertices of cube
		glBindVertexArray(VAO_cube);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   //interpret the colours
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		
		//VAO of axis
		glGenVertexArrays(1, &VAO_axis);
		glGenBuffers(1, &VBO_axis); //stores vertices of cube

		glBindVertexArray(VAO_axis);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_axis);
		glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   //interpret the colours
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

        //VAO OF CIRCLE
        glGenVertexArrays(1, &VAO_circle);
        glGenBuffers(1, &VBO_cirle); //stores vertices of cube

        glBindVertexArray(VAO_circle);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_cirle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
        glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);


        //VAO of grid
        glGenVertexArrays(1, &VAO_grid);
        glGenBuffers(1, &VBO_grid); //stores vertices of cube

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO_grid);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_grid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gridVertices), gridVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //tells gpu how to interpret vertices for positions
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));   //interpret the colours
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);


		//initial placement of students in world
		for (int i = 0; i < 5; i++)
		{
			studentMatrixArray[i] = glm::mat4(1.0f);
			studentMatrixArray[i] = glm::translate(studentMatrixArray[i], glm::vec3(0.0f, 0.0f, (float)(i * -5)));
		}

		
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
			processPolygonMode(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); //the view is updated every frame because cameraPos is dynamically changed with keyboard input and cameraFront is dynamically changed with cursor movement
			projection = glm::perspective(glm::radians(fieldOfView), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); //the perspective is updated every frame because the fieldOfView is dynamically changed by zooming

			//pass updated settings to the shader
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(VAO_grid);
            drawGrid(shaderProgram, glm::vec3(0.0f, 0.0f, 0.0f));
            
            glBindVertexArray(VAO_axis);
            drawLines(shaderProgram);

            glBindVertexArray(VAO_circle);
			drawCircle(shaderProgram);
            glBindVertexArray(VAO_cube);
			drawJulie(shaderProgram, studentMatrixArray[0]);
			drawClaudia(shaderProgram, studentMatrixArray[1]);
			drawCamil(shaderProgram, studentMatrixArray[2]);
			drawCharles(shaderProgram, studentMatrixArray[3]);
            drawMax(shaderProgram, studentMatrixArray[4]);
            
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		//de-allocate all resources
		/*glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);*/
		glDeleteProgram(shaderProgram);

		glfwTerminate();
		return 0;
	}

	void drawGrid(int shaderProgram, glm::vec3 translationMatrix) {
        const int AMOUNT_OF_LINES = 128;

        glm::mat4 gridMatrix = glm::mat4(1.0f);
        gridMatrix = glm::translate(gridMatrix, translationMatrix);

        glm::mat4 transform = glm::mat4(1.0f);
        glm::mat4 worldMatrix = glm::mat4(1.0f);
        worldMatrix = gridMatrix * transform;
        unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

        glDrawArrays(GL_LINES, 0, 2);

        //parallel to z axis
        for(int i = 0; i <= AMOUNT_OF_LINES; i++) {
            transform = glm::mat4(1.0f);

            if(i < AMOUNT_OF_LINES/2) {
                //move to the left of z axis (-x)
                transform = glm::translate(transform, glm::vec3(-i, 0.0f, -AMOUNT_OF_LINES/2));

            } else if (i == AMOUNT_OF_LINES/2) {
                //most left line (-x)
                transform = glm::translate(transform, glm::vec3(-AMOUNT_OF_LINES/2, 0.0f, -AMOUNT_OF_LINES/2));

            } else {
                //move to the right of z axis (+x)
                transform = glm::translate(transform, glm::vec3(i-(AMOUNT_OF_LINES/2), 0.0f, -AMOUNT_OF_LINES/2));
            }

            transform = glm::scale(transform, glm::vec3(0.0f, 0.0f, AMOUNT_OF_LINES));

            worldMatrix = gridMatrix * transform;
            glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
            glDrawArrays(GL_LINES, 0, 4);
        }

        //parallel to x axis
        for(int i = 0; i <= AMOUNT_OF_LINES; i++) {
            transform = glm::mat4(1.0f);

            if(i < AMOUNT_OF_LINES/2) {
                //move after x axis (-z)
                transform = glm::translate(transform, glm::vec3(-AMOUNT_OF_LINES/2, 0.0f, -i));

            } else if(i == AMOUNT_OF_LINES/2) {
                //farthest (-z)
                transform = glm::translate(transform, glm::vec3(-AMOUNT_OF_LINES/2, 0.0f, -AMOUNT_OF_LINES/2));

            } else {
                //move before x axis (+z)
                transform = glm::translate(transform, glm::vec3(-AMOUNT_OF_LINES/2, 0.0f, i-AMOUNT_OF_LINES/2));
            }

            transform = glm::scale(transform, glm::vec3(AMOUNT_OF_LINES, 0.0f, 0.0f));

            worldMatrix = gridMatrix * transform;
            glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
            glDrawArrays(GL_LINES, 0, 4);
        }
    }

    void drawLines(int shaderProgram){
        
        //worldMatrix = position of lines in world
		glm::mat4 worldMatrix = glm::mat4(1.0f);

		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));

		glDrawArrays(GL_LINES, 0, 6);
    }

	void drawCircle(int shaderProgram)
	{
		//worldMatrix = position of lines in world
        glm::mat4 transform = glm::mat4(1.0f); //starts as a clean identity matrix
        transform = glm::mat4(1.0f); //important! transform matrix need to be set back to a clean state (identity matrix) because we are transforming a new cube!
        transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //second rotate
        glm::mat4 worldMatrix = transform * glm::mat4(1.0f);
		unsigned int worldMatrixLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 30);
	}
    
	void drawJulie(int shaderProgram, glm::mat4 studentMatrix)
	{
		//draw letters
		LetterHelper::drawJ(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::drawP(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw5(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
	}

    void drawCharles(int shaderProgram, glm::mat4 studentMatrix){

        //draw letters
        LetterHelper::drawC(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix); //check this function for detailed explanation
        LetterHelper::drawR(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw3(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
    }

	void drawClaudia(int shaderProgram, glm::mat4 studentMatrix) {
        
        //draw letters
        LetterHelper::drawC(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::drawG(shaderProgram, glm::vec3(-2.0f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw2(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw9(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
	}

	void drawMax(int shaderProgram, glm::mat4 studentMatrix)
	{
        //draw letters
        LetterHelper::drawN(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix); //check this function for detailed explanation
        LetterHelper::drawS(shaderProgram, glm::vec3(-2.3f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw9(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
    }

	void drawCamil(int shaderProgram, glm::mat4 studentMatrix)
	{
		//draw letters
        LetterHelper::drawC(shaderProgram, glm::vec3(-4.0f, 0.0f, 0.0f), studentMatrix); //check this function for detailed explanation
        LetterHelper::drawB(shaderProgram, glm::vec3(-2.5f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw4(shaderProgram, glm::vec3(1.6f, 0.0f, 0.0f), studentMatrix);
        LetterHelper::draw1(shaderProgram, glm::vec3(3.5f, 0.0f, 0.0f), studentMatrix);
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
			enablePan = true;
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) //disable pan when released
			enablePan = false;
		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) //enable tilt when pressed
			enableTilt = true;
		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) //disable tilt when released
			enableTilt = false;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) //enable zoom when pressed
			enableZoom = true;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) //disable zoom when released
			enableZoom = false;
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

	//documentation: https://www.glfw.org/docs/3.3/input_guide.html
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//transform student
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
			moveModelUp();
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
			moveModelLeft();
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
			moveModelDown();
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
			moveModelRight();
		if (key == GLFW_KEY_U && action == GLFW_PRESS)
			scaleModelUp();
		if (key == GLFW_KEY_J && action == GLFW_PRESS)
			scaleModelDown();
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
			rotateModelLeft();
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
			rotateModelRight();
	}

	//change polygon mode
	//source: https://knowww.eu/nodes/59b8e93cd54a862e9d7e407c
	void processPolygonMode(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	//process keyboard input
	//source: https://learnopengl.com/Getting-started/Camera
	void processInput(GLFWwindow * window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
        
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			currentStudent = 0;
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			currentStudent = 1;
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
			currentStudent = 2;
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			currentStudent = 3;
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
			currentStudent = 4;
        if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS
           || glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS){
            currentStudent = -1;
        }
		//fly around
		float cameraSpeed = 5 * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			cameraPos = cameraPos + cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			cameraPos = cameraPos - cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			cameraPos = cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			cameraPos = cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	////scales up currentStudent by 0.1
	void scaleModelUp()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::scale(studentMatrixArray[currentStudent], glm::vec3(1.1f, 1.1f, 1.1f));
	}

	//scales down currentStudent by 0.1
	void scaleModelDown()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::scale(studentMatrixArray[currentStudent], glm::vec3((float)(1.0/1.1), (float)(1.0/1.1), (float)(1.0/1.1)));
	}
	


	//moves the currentStudent 5 units to the left
	void moveModelLeft()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::translate(studentMatrixArray[currentStudent], glm::vec3(-5.0f, 0.0f, 0.0f));
	}

	//moves currentStudent 5 units to the right
	void moveModelRight()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::translate(studentMatrixArray[currentStudent], glm::vec3(5.0f, 0.0f, 0.0f));
	}

	//moves currentStudent 5 units up
	void moveModelUp()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::translate(studentMatrixArray[currentStudent], glm::vec3(0.0f, 5.0f, 0.0f));
	}

	//moves currentStudent 5 units down
	void moveModelDown()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::translate(studentMatrixArray[currentStudent], glm::vec3(0.0f, -5.0f, 0.0f));
	}

	//rotates currentStudent left
	void rotateModelLeft()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::rotate(studentMatrixArray[currentStudent], glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	
	//rotates currentStudent right
	void rotateModelRight()
	{
		if (currentStudent >= 0 && currentStudent <= 4)
			studentMatrixArray[currentStudent] = glm::rotate(studentMatrixArray[currentStudent], glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

