#include "util/GLUtil.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "rendering/Model.h"
#include "GameObject.h"
//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//C++ includes
#include <iostream>
#include <string>
#include <cmath>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
*/

int main() {

	/* Initialize the library */
	if(!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	if(glewInit() != GLEW_OK) {
		std::cout << "GLEW init failed!" << std::endl;
	} else {
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GL Shader Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	}

	Model* teapot = new Model;
	teapot->loadModel("res/models/utah_teapot.obj");

	GameObject* go = new GameObject(teapot);

	glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, .3f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(), glm::vec3());

	Shader* shader = new Shader("res/shaders/basic.shader");

	Renderer* rend = new Renderer;

	std::cout << std::endl;
	double lastPrint = glfwGetTime();
	unsigned numFrames = 0;
	unsigned long totalFrames = 0;
	/* Loop until the user closes the window */
	while(!glfwWindowShouldClose(window)) {
		
		rend->clear();
		/* Render here */
		float x = 2*std::cosf(totalFrames/20.0f);
		float y = 2*std::sinf(totalFrames/20.0f);
		go->setPosition(Vec3d(x, y, 0));

		auto model = glm::rotate(go->getTranslateMat(), x, glm::vec3(1, 0, 0));

		shader->use_program();
		shader->setUniform4f("u_Color", .1f, .3f, .7f, 1);
		shader->setUniformMat4f("u_MVP", proj * view * model);
		go->draw(rend, shader);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		numFrames++;
		totalFrames++;
		if(lastPrint + 1 <= glfwGetTime()) {
			std::cout << 1000.0 / numFrames << "ms per frame" << std::endl;
			numFrames = 0;
			lastPrint++;
		}

	}

	delete shader;
	delete go;

	glfwTerminate();

	return 0;
}