#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//Resize viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void drawSquare() {
	//points
	float vertices[] = {
		0.5f, -0.5f, 0.0f, //top right
		0.5f, -0.5f, 0.0f, //bottom right
	   -0.5f, -0.5f, 0.0f, //bottom left
	   -0.5f,  0.5f, 0.0f  //top left
	};

	//indices of points used to draw
	unsigned int indices[] = {
		0, 1, 3, //first triangle
		1, 2, 3 //second triangle
	};

	//Element Buffer Object is a buffer just like vertex buffer object but this stores indices that opengl uses to decide what to draw.
	//This is know as index drawing
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//bind the EBO
	glBindBuffer(GL_ARRAY_BUFFER, EBO);
	//copy indices into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

int createVertexShader() {
	//vertex shader all about handling individual vertices
	const char* vertexShaderSource = "#version 330 core\n layout(location = 0) in vec3 aPos;\n void main() \n{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  vertexSuccess;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);

	if (!vertexSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!! VERTEX SHADER\n" << std::endl;
	}

	return vertexShader;

}

int createFragmentShader() {
	//fragment shader all about calculating color output for pixels
	//this one simply paints the pixels orange
	const char* fragmentShaderSource = "#version 330 core \n out vec4 FragColor;\n void main() \n{FragColor = vec4(1.0f,0.5f,0.2f,1.0f); \n}";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int fragmentSuccess;
	char infoLog[512];

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);

	if (!fragmentSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!! FRAGMENT SHADER\n" << std::endl;
	}


	return fragmentShader;

}

void drawTriangle() {
	//vertex shader all about handling individual vertices
	const char* vertexShaderSource = "#version 330 core\n layout(location = 0) in vec3 aPos;\n void main() \n{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";
	//fragment shader all about calculating color output for pixels
	const char* fragmentShaderSource = "#version 330 core \n out vec4 FragColor;\n void main() \n{FragColor = vec4(1.0f,0.5f,0.2f,1.0f); \n}";

	//(X,Y)
	///////////////////////
	//         | (0,1)  //
	//         |        //
	//    (0,0)|  (1,0) //
	//--------------------
	// (-1,0)  |        //
	//         |        //
	//         |(0,-1)  //
	//////////////////////
	//x , y, z
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	//vertice buffer object id
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//bind buffer object to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//copy the vertices data int the bound buffer
    //GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
	//GL_DYNAMIC_DRAW : the data is likely to change a lot.
	//GL_STREAM_DRAW : the data will change every time it is drawn.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int  vertexSuccess; 
	int fragmentSuccess;
	char infoLog[512];

	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);

	if (!vertexSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!! VERTEX SHADER\n" << std::endl;
	}

	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);

	if (!fragmentSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!! FRAGMENT SHADER\n" << std::endl;
	}

	//shader is final linked version of multpile shaders combined. To use sahders we have to link them to shader program object
	//and then activate the shader program when rendering objects. The activated shader programs shaders will be used when we issue render calls
	unsigned int shaderProgram;
    
	//creates program and returns id to reference it
	shaderProgram = glCreateProgram();

	//attach shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link program
	glLinkProgram(shaderProgram);

	int linkSuccess;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
	
	if (!linkSuccess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SUCCESS!! SHADER PROGRAM\n" << std::endl;
	}

	//activate program
	glUseProgram(shaderProgram);

	// delete shaders after they have been linked into the program because they are nolonger needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//each vertex attribute takes its data from memory managed by a VBO/VBOs. The VBO/s that it uses is determeined by the ones currently
	//bound to GL_ARRAY_BUFFER
	//USE vertex array objects (VAO) can be bound just like a vertex buffer object and any subsequent calls will be stored in VAO. When configuring
	//vertex attribute pointers you only have to make those calls once and then whne you want to draw the object just bind the corresponding VAO. This
	//makes switching and addiung different vertex data very easy

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// INITIALIZATION CODE - done once unless your object frequently changes
	// 1. bind vertice array object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OPENGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
		//tell opengl how it should interpret the vertex data per vertex attribute
		// params:-
		// 1. which vertex we want to configure (point on screen)
		// 2. size of vertex attribute is a vec3 (x,y,z)
		// 3. type of the data
		// 4. specifies whether we want the data to be normalized
		// 5. is the 'stride' which is the space between each consecutive vertex attribute sets - [x,y,z,x,y,z]
		// 6. offset of where the position data begins in buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//enable the first vertices in the array
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	//GL_TRIANGLE is opengl primitive type
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



int main() {

	//initiaise GLFW
	glfwInit();

	//Set what major version of opengl that glfw should expect
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Set what minor version of opengl that glfw should expect
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Set that we want to use CORE mode rather than INTERMIDIATE mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create GLFW window with dimensions and title
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);


	//GLAD manages function pointers for OpenGL so we initialise it here
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Set view port (rendering window) with dimensions
	//first two parameters set location of lower left hand corner
	glViewport(0, 0, 800, 600);

	//The moment a user resizes the window the viewport should be adjusted as well. 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	

	//While window wasnt closed swap the render buffers - opengl is double buffered one in foreground and one in background
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		//listen for events such as mouse press
		glfwPollEvents();

		drawTriangle();
	}

	//clean up
	glfwTerminate();

	return 0;
}


