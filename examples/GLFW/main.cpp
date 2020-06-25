#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>

int main(int _argc, char** _argv) {


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;

}