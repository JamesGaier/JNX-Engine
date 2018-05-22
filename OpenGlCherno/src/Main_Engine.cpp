#include "rendering/Renderer.h"
#include "rendering/buffers/VertexBuffer.h"
#include "rendering/buffers/IndexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//C++ includes
#include <iostream>
#include <string>

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


	const unsigned int VERTEX_BUFFER_COUNT = 8;
	const float* const vertex_buffer = new float[VERTEX_BUFFER_COUNT] {
		-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f,
	};

	const unsigned int INDICE_COUNT = 6;
	const unsigned int* indicies = new unsigned int[INDICE_COUNT] {
		0, 1, 2,
			2, 3, 0
	};

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);

	VertexBuffer* vb = new VertexBuffer(vertex_buffer, VERTEX_BUFFER_COUNT * sizeof(float));
	VertexBufferLayout* vbl = new VertexBufferLayout;
	vbl->push<float>(2);
	
	VertexArray* va = new VertexArray;
	va->addBuffer(vb, vbl);

	IndexBuffer* ib = new IndexBuffer(indicies, INDICE_COUNT);

	Shader* shader = new Shader("res/shaders/basic.shader");

	Renderer* rend = new Renderer;

	double lastPrint = glfwGetTime();
	unsigned numFrames = 0;
	/* Loop until the user closes the window */
	while(!glfwWindowShouldClose(window)) {
		
		rend->clear();
		/* Render here */
		shader->use_program();
		shader->setUniform4f("u_Color", .1f, .3f, .7f, 1);
		shader->setUniformMat4f("u_MVP", proj);
		rend->draw(va, ib, shader);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		numFrames++;
		if(lastPrint + 1 <= glfwGetTime()) {
			std::cout << 1000.0 / numFrames << "ms per frame" << std::endl;
			numFrames = 0;
			lastPrint++;
		}

	}

	delete vb;
	delete ib;
	delete shader;

	glfwTerminate();

	delete[] vertex_buffer;
	delete[] indicies;

	return 0;
}