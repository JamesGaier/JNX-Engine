#define _USE_MATH_DEFINES
#include "JNX_Engine.h"
#include "util/GLUtil.h"
#include "rendering/Texture.h"
#include "rendering/Model.h"
#include "GameObject.h"
//C++ includes
#include <iostream>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
*/

void ortho(JNX_Engine& jnx) {
	jnx.setProjectionOrtho(-10, 10, 10, -10);
	jnx.setCameraTranslate(Vec3d(0,0,-1));
	jnx.loadShader("res/shaders/basic.shader");

	auto sqr = new Model();
	if(sqr->loadSquare(.5f)) {
		auto test = new GameObject(sqr);
		test->setPosition(Vec3d(0));
		jnx.registerGameObject(test);
	}
}

void prespective(JNX_Engine& jnx) {
	jnx.setProjectionPerspective(glm::radians(45.0f));
	jnx.setCameraTranslate(Vec3d(0, 0, -5));
	jnx.loadShader("res/shaders/basic.shader");

	//Longest part of init sequence
	jnx.registerGameObject(new GameObject("res/models/teapot.obj"));
}

int main() {

	constexpr bool orthoTest = false;
	JNX_Engine jnx(800, 600, true);

	if(!jnx.isLoaded())
		return 0;

	std::cout << std::endl;

	if(orthoTest)
		ortho(jnx);
	else
		prespective(jnx);

	std::cout << std::endl;

	/* Loop until the user closes the window */
	while(jnx.running()) {
		jnx.cleanBuffers();
		
		/* Render here */
		jnx.updateGameObjects();
		jnx.renderGameObjects();

		/* Swap front and back buffers */
		jnx.swapBuffers();

		/* Poll for and process events */
		glfwPollEvents();
	}

	jnx.cleanRegisteredGOs();

	return 0;
}
