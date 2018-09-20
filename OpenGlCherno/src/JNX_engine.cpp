#include "JNX_Engine.h"
#include "util/GLUtil.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <iomanip>

JNX_Engine::JNX_Engine(unsigned wide, unsigned high, bool vsync, std::string name, bool initNow) :gameName(name), loaded(false), width(wide), height(high) {
	if(initNow) {
		init(vsync);
	}
}

JNX_Engine::~JNX_Engine() {
	cleanRegisteredGOs();
	glfwTerminate();
}

bool JNX_Engine::init(bool vsync) {
	/* Initialize the library if we have not already loaded */
	if(loaded || !glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, gameName.c_str(), NULL, NULL);
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

int JNX_Engine::minIndex(size_t sortedIndex) {
	int min_index = -1;
	unsigned char min_val = 255;
	const auto size = numRegisteredObjects();

	for(size_t i = 0; i < size; i++) {
		const auto curr = gameObjects.front();
		gameObjects.pop();  // This is dequeue() in C++ STL

		// we add the condition i <= sortedIndex
		// because we don't want to traverse
		// on the sorted part of the queue,
		// which is the right part.
		if(curr->renderLayer() <= min_val && i <= sortedIndex) {
			min_index = i;
			min_val = curr->renderLayer();
		}
		gameObjects.push(curr);  // This is enqueue() in C++ STL
	}
	return min_index;
}

// Moves given minimum element to rear of queue
void JNX_Engine::insertMinToRear(int min_index) {
	GameObject* min_val;
	const auto size = numRegisteredObjects();
	for(size_t i = 0; i < size; i++) {
		const auto curr = gameObjects.front();
		gameObjects.pop();
		if(i != min_index)
			gameObjects.push(curr);
		else
			min_val = curr;
	}
	gameObjects.push(min_val);
}

void JNX_Engine::sortRenderQueue() {

	if(numRegisteredObjects() == 1) { return; }
	for(size_t i = 1; i <= numRegisteredObjects(); i++) {
		const auto min_index = minIndex(numRegisteredObjects() - i);
		insertMinToRear(min_index);
	}

	isRenderSorted = true;
}

void JNX_Engine::registerGameObject(GameObject* go) {
	
	gameObjects.push(go);
	go->onRegistered();
	isRenderSorted = false;
}

void JNX_Engine::renderGameObject(GameObject * go) const {
	go->shaderSettings(viewProjection());
	go->draw();
}

void JNX_Engine::renderGameObjects() {
	if(!isRenderSorted && sortRender_flag) {
		sortRenderQueue();
	}

	const auto size = numRegisteredObjects();
	for(size_t i = 0; i < size; i++) {
		auto go = gameObjects.front();
		gameObjects.pop();
		renderGameObject(go);
		gameObjects.push(go);
	}
}

void JNX_Engine::updateGameObjects() {
	const auto size = numRegisteredObjects();
	for(size_t i = 0; i < size; i++) {
		const auto go = gameObjects.front();
		gameObjects.pop();
		go->update(time() - lastDelta);
		gameObjects.push(go);
	}

	lastDelta = time();
}

void JNX_Engine::cleanRegisteredGOs(bool deleteCall) {
	
	while(numRegisteredObjects() > 0) {
		if(deleteCall) {
			delete gameObjects.front();
		}
		gameObjects.pop();
	}
	isRenderSorted = true;
}
