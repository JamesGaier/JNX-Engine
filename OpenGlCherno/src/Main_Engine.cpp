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
*/

int main() {

	JNX_Engine jnx(true);

	if(!jnx.isLoaded()) {
		return 0;
	}

	//Longest part of init sequence
	Model* teapot = new Model("res/models/utah_teapot.obj");
	GameObject* go = new GameObject(teapot);

	jnx.setProjectionOrtho(-10.0f, 10.0f, -7.5f, 7.5f, .3f, 500.0f);
	jnx.setCameraTranslate(Vec3d());

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
		float x = 2*std::cosf(totalFrames/20.0f);
		float y = 2*std::sinf(totalFrames/20.0f);
		go->setPosition(Vec3d(x, y, 0));

		auto model = glm::rotate(go->getTranslateMat(), x, glm::vec3(1, 0, 0));

		shader->use_program();
		shader->setUniform4f("u_Color", .1f, .3f, .7f, 1);
		shader->setUniformMat4f("u_MVP", jnx.viewProjection() * model);
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