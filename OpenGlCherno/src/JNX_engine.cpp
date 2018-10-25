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

void JNX_Engine::sortRenderQueue() {
	std::sort(gameObjects.begin(), gameObjects.end(),
			  [ ](auto i, auto j) {
		return i->renderLayer() < j->renderLayer();
	});

	isRenderSorted = true;
}

void JNX_Engine::registerGameObject(std::shared_ptr<GameObject> go) {
	gameObjects.push_back(go);
	go->onRegistered();
	isRenderSorted = false;
}

void JNX_Engine::renderGameObject(GameObject& go) const {
	go.shaderSettings(viewProjection());
	go.draw();
}

void JNX_Engine::renderGameObjects() {
	if(!isRenderSorted && sortRender_flag) {
		sortRenderQueue();
	}

	std::for_each(gameObjects.begin(), gameObjects.end(),
				  [=](auto go) { renderGameObject(*go); }
	);
}

void JNX_Engine::updateGameObjects() {
	std::for_each(gameObjects.begin(), gameObjects.end(),
				  [=](auto go) {go->update(time() - lastDelta); });

	lastDelta = time();
}

void JNX_Engine::cleanRegisteredGOs() {
	gameObjects.clear();

	isRenderSorted = true;
}
