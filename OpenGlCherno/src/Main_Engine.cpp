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
#include <obj_loader/OBJ_Loader.h>
//C++ includes
#include <iostream>
#include <string>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
*/

#define UTAH 1

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

	unsigned int VERTEX_BUFFER_COUNT = 8;
	float* vertex_buffer = new float[VERTEX_BUFFER_COUNT] {
		-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f,
	};

	unsigned int INDICE_COUNT = 6;
	unsigned int* indicies = new unsigned int[INDICE_COUNT] {
		0, 1, 2,
			2, 3, 0
	};

	objl::Loader loader;

	if(UTAH && loader.LoadFile("res/models/utah_teapot.obj")) {
	
		std::cout << "Found a teapot from Utah" << std::endl;

		delete[] vertex_buffer;
		
		VERTEX_BUFFER_COUNT = loader.LoadedVertices.size() * 3;
		vertex_buffer = new float[VERTEX_BUFFER_COUNT];

		int currentIndex = 0;
		for(unsigned i = 0; i < loader.LoadedVertices.size(); i++) {
			objl::Vector3 data = loader.LoadedVertices[i].Position;
			vertex_buffer[currentIndex] = data.X;
			vertex_buffer[currentIndex + 1] = data.Y;
			vertex_buffer[currentIndex + 2] = data.Z;
			currentIndex += 3;
		}

		delete[] indicies;

		INDICE_COUNT = loader.LoadedIndices.size();
		indicies = new unsigned int[INDICE_COUNT];

		for(unsigned i = 0; i < loader.LoadedIndices.size(); i++) {
			*(indicies + i) = loader.LoadedIndices[i];
		}

		std::cout << "Successfully loaded Utah teapot" << std::endl;
	}
	
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);

	VertexBuffer* vb = new VertexBuffer(vertex_buffer, VERTEX_BUFFER_COUNT * sizeof(float));
	VertexBufferLayout* vbl = new VertexBufferLayout;
	vbl->push<float>(2 + UTAH);
	
	VertexArray* va = new VertexArray;
	va->addBuffer(vb, vbl);

	IndexBuffer* ib = new IndexBuffer(indicies, INDICE_COUNT);

	Shader* shader = new Shader("res/shaders/basic.shader");

	Renderer* rend = new Renderer;

	std::cout << std::endl;
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