#define _USE_MATH_DEFINES
#include "JNX_Engine.h"
#include "util/GLUtil.h"
#include "rendering/Texture.h"
#include "rendering/Model.h"
#include "GameObject.h"
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

	JNX_Engine jnx(640, 480);

	if(!jnx.isLoaded()) 
		return 0;
	
	//Longest part of init sequence
	Model* circle = new Model("res/models/circle.obj");
	GameObject* go = new GameObject(circle);

	jnx.setProjectionPerspective(glm::radians(45.0f));
	jnx.setCameraTranslate(Vec3d(0, 0, -5));
	jnx.loadShader("res/shaders/basic.shader");

	jnx.registerGameObject(go);

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

	delete go;

	return 0;
}