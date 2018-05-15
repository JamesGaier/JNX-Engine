#include "rendering/Renderer.h"
#include "rendering/buffers/VertexBuffer.h"
#include "rendering/buffers/IndexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/Shader.h"
//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

	VertexBuffer* vb = new VertexBuffer(vertex_buffer, VERTEX_BUFFER_COUNT * sizeof(float));
	VertexBufferLayout* vbl = new VertexBufferLayout;
	vbl->push<float>(2);
	
	VertexArray* va = new VertexArray;
	va->addBuffer(vb, vbl);

	IndexBuffer* ib = new IndexBuffer(indicies, INDICE_COUNT);

	Shader* shader = new Shader("res/shaders/basic.shader");
	shader->use_program();
	int location = shader->uniform_location("u_Color");

	double lastPrint = glfwGetTime();
	unsigned numFrames = 0;
	/* Loop until the user closes the window */
	while(!glfwWindowShouldClose(window)) {

		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
		/* Render here */
		GLCALL(glUniform4f(location, 0.1f, 0.1f, .5f, 1.0f));
		
		va->Bind();
		ib->Bind();
		GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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