#include "JNX_Engine.h"
#include "util/GLUtil.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

JNX_Engine::JNX_Engine(bool initNow) : loaded(false) {
	if(initNow) {
		init();
	}
}

JNX_Engine::~JNX_Engine() { 
	glfwTerminate();
}

bool JNX_Engine::init(bool vsync) {
	
	if(loaded) 
		return false;
	
	/* Initialize the library */
	if(!glfwInit())
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
