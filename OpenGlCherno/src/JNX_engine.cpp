#include "JNX_Engine.h"
#include "util/GLUtil.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <iomanip>

JNX_Engine::JNX_Engine(unsigned wide, unsigned high, bool vsync, bool initNow) : loaded(false), width(wide), height(high) {
	if(initNow) {
		init(vsync);
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
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if(vsync) {
		glfwSwapInterval(1);
	} else {
		glfwSwapInterval(0);
	}

	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	if(glewInit() != GLEW_OK) {
		std::cerr << "GLEW init failed!" << std::endl;
		return false;
	}

	Input::registerAsCallback(window);

	loaded = true;

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL Shader Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	std::cout << "JNX Engine Version: " << version() << std::endl;
	return isLoaded();
}

void JNX_Engine::setProjectionOrtho(float left, float right, float up, float down) {
	proj = glm::ortho(left, right, up, down);
	projMode = ProjectionMode::ORTHO;
}

void JNX_Engine::setOrthoCoordsFromCenter(float height) {
	const auto half = height / 2;
	setProjectionOrtho(-half * aspectRatio(), half * aspectRatio(), half, -half);
	setCameraTranslate(Vec3d(0));
}

void JNX_Engine::setOrthoCoordsFromTopLeft(float height) {
	setProjectionOrtho(0, height * aspectRatio(), 0, -height);
	setCameraTranslate(Vec3d(height / 2, height / 2, 0));
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
		if(printFrameTime) {
			using namespace std;
			cout << setw(10) << setprecision(7) << 1000.0 / static_cast<double>(numFrames) << "ms per frame (" << numFrames << " FPS)" << endl;
		}
		lastFPS = numFrames;
		numFrames = 0;
		lastPrint++;
	}
}

void JNX_Engine::renderGameObject(GameObject * go) const {
	go->shaderSettings(shader, viewProjection());
	go->draw(shader);
}

void JNX_Engine::renderGameObjects() const {
	for(const auto& go : gameObjects) {
		renderGameObject(go);
	}
}

void JNX_Engine::updateGameObjects() {
	for(const auto& go : gameObjects) {
		go->update(time() - lastDelta);
	}

	lastDelta = time();
}

void JNX_Engine::cleanRegisteredGOs(bool deleteCall) {
	if(deleteCall) {
		for(auto go : gameObjects) { delete go; }
	}
	gameObjects.clear();
}
