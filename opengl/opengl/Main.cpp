#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//Resize viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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

	//While widow wasnt closed swap the render buffers - opengl is double buffered one in foreground and one in background
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		//listen for events such as mouse press
		glfwPollEvents();
	}

	//clean up
	glfwTerminate();

	return 0;
}

