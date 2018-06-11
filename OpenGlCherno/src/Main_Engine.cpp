#define _USE_MATH_DEFINES
#include "util/GLUtil.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "rendering/Model.h"
#include "GameObject.h"
#include "JNX_Engine.h"
//OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//C++ includes
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
*/

int main() {

	JNX_Engine jnx(true);

	if(!jnx.isLoaded()) {
		return 0;
	}

	//Longest part of init sequence
	Model* circle = new Model("res/models/circle.obj");
	GameObject* go = new GameObject(circle);
	std::cout << "Scale Factor: " << circle->scaleFactor() << std::endl;
	go->setScale(Vec3d(circle->scaleFactor()));
	go->setRotation(static_cast<float>(M_1_PI), Vec3d(0, 0, -1));

	jnx.setProjectionPerspective(glm::radians(45.0f), 4.0f / 3.0f);
	jnx.setCameraTranslate(Vec3d(0, 0, -5));

	Shader* shader = new Shader("res/shaders/basic.shader");
	
	Renderer* rend = new Renderer;

	std::cout << std::endl;
	double lastPrint = glfwGetTime();
	unsigned numFrames = 0;
	unsigned long totalFrames = 0;
	/* Loop until the user closes the window */
	while(jnx.running()) {
		
		rend->clear();
		/* Render here */
		float x = std::cosf(totalFrames/20.0f);
		float y = std::sinf(totalFrames/20.0f);
		go->setPosition(Vec3d(x, y, 0));

		shader->use_program();
		shader->setUniform4f("u_Color", .1f, .3f, .7f, 1);
		shader->setUniformMat4f("u_MVP", jnx.viewProjection() * go->getModelMatrix());
		go->draw(rend, shader);
		/* Swap front and back buffers */
		jnx.swapBuffers();

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

	return 0;
}