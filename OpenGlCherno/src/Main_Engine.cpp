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

	JNX_Engine jnx;

	if(!jnx.isLoaded()) {
		return 0;
	}

	//Longest part of init sequence
	Model* circle = new Model("res/models/circle.obj");
	GameObject* go = new GameObject(circle);

	jnx.setProjectionPerspective(glm::radians(45.0f), 4.0f / 3.0f);
	jnx.setCameraTranslate(Vec3d(0, 0, -5));
	jnx.loadShader("res/shaders/basic.shader");

	/* Loop until the user closes the window */
	while(jnx.running()) {
		
		jnx.cleanBuffers();
		/* Render here */
		const int RATE = 20;
		float x = std::cosf(jnx.totalFrameCount() / static_cast<float>(RATE));
		float y = std::sinf(jnx.totalFrameCount() / static_cast<float>(RATE));
		go->setPosition(Vec3d(x, y, 0));

		jnx.shaderManip()->setUniform4f("u_Color", .1f, .3f, .7f, 1);
		jnx.shaderManip()->setUniformMat4f("u_MVP", jnx.mvp(go));
		jnx.renderGameObject(go);

		/* Swap front and back buffers */
		jnx.swapBuffers();

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete go;

	return 0;
}