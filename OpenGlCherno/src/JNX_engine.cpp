#include "JNX_Engine.h"
#include "util/GLUtil.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

JNX_Engine::JNX_Engine(unsigned wide, unsigned high, bool initNow) : loaded(false), width(wide), height(high) {
	if(initNow) {
		init();
	}
}

JNX_Engine::~JNX_Engine() {
	delete shader;
	glfwTerminate();
}

bool JNX_Engine::init(bool vsync) {
	
	/* Initialize the library if we have not already loaded */
	if(loaded || !glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if(vsync) 
		glfwSwapInterval(1);

	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	if(glewInit() != GLEW_OK) {
		std::cout << "GLEW init failed!" << std::endl;
		return false;
	}
	
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL Shader Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	
	loaded = true;

	return true;
}

void JNX_Engine::setProjectionOrtho( float left, float right, float up, float down, float near, float far) {
	proj = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, .3f, 500.0f);
	projMode = ProjectionMode::ORTHO;
}

void JNX_Engine::setProjectionPerspective(float fov, float aspectRatio, float near, float far) {
	proj = glm::perspective(fov, aspectRatio, near, far);
	projMode = ProjectionMode::PERSPECTIVE;
}

void JNX_Engine::setCameraTranslate(const Vec3d & pos) {
	trans = glm::translate(glm::mat4(), static_cast<glm::vec3>(pos));
}

void JNX_Engine::loadShader(const std::string & file) {
	shader = new Shader(file);
	shader->use_program();
}

void JNX_Engine::swapBuffers() {
	glfwSwapBuffers(window); 

	numFrames++;
	totalFrames++;
	if(lastPrint + 1 <= time()) {
		std::cout << 1000.0 / numFrames << "ms per frame" << std::endl;
		lastFPS = numFrames;
		numFrames = 0;
		lastPrint++;
	}
}

void JNX_Engine::renderGameObject(GameObject * go) const {
	go->shaderSettings(shader, viewProjection());
	go->draw(rend, shader);
}

void JNX_Engine::renderGameObjects() const {
	for(unsigned i = 0; i < gameObjects.size(); i++) {
		renderGameObject(gameObjects[i]);
	}
}

void JNX_Engine::updateGameObjects() {
	
	for(unsigned i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update(time() - lastDelta);
	}

	lastDelta = time();
}
