#define _USE_MATH_DEFINES
#include "JNX_Engine.h"
#include "util/GLUtil.h"
#include "rendering/Texture.h"
#include "rendering/Model.h"
#include "TexturedGameObject.h"
//C++ includes
#include <iostream>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
*/

void ortho(JNX_Engine& jnx) {
	constexpr auto high = 10;
	jnx.setOrthoCoordsFromCenter(high);

	auto sqr = new Model();
	if(sqr->loadSquare(1.75f, true)) {
		jnx.registerGameObject(new TexturedGameObject(sqr, "res/textures/test.png"));
	}
}

void prespective(JNX_Engine& jnx) {
	jnx.setProjectionPerspective(glm::radians(45.0f));
	jnx.setCameraTranslate(Vec3d(0, 0, -5));

	jnx.registerGameObject(new GameObject("res/models/teapot.obj", "res/shaders/basic.shader"));
}

int main() {
	constexpr bool orthoTest = true;
	auto jnx = JNX_Engine(800, 600, true, "JNX Test " + JNX_Engine::version());

	if(!jnx.isLoaded())
		return 0;

	std::cout << std::endl;

	if(orthoTest)
		ortho(jnx);
	else
		prespective(jnx);

	std::cout << std::endl;

	jnx.setSortRenderFlag();
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

	return 0;
}
