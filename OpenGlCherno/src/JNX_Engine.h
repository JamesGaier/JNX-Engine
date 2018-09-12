#ifndef _JNX_ENGINE
#define _JNX_ENGINE

#include "util/Vec3d.h"
#include "rendering/Shader.h"
#include "rendering/Renderer.h"
#include "Input.h"
#include "GameObject.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <queue>

/*
* Purpose: Central include for JNX engine
* @author Nicholas Baron
*
*/
enum class ProjectionMode { ORTHO, PERSPECTIVE };

class JNX_Engine {
private:
	static constexpr auto Z_NEAR = 0.1f, Z_FAR = 100.0f;

	GLFWwindow* window;

	unsigned char maxCurrentRender = 0;
	std::queue<GameObject*> gameObjects;

	std::string gameName;
	unsigned width, height;

	bool loaded;
	glm::mat4 proj, trans;

	ProjectionMode projMode;

	//Frame counting variables
	double lastPrint = time(), lastDelta = time();
	unsigned numFrames, lastFPS;
	unsigned long totalFrames;
	bool printFrameTime = true;

	int minIndex(size_t sortedIndex);
	void insertMinToRear(int min_index);
public:
	JNX_Engine(unsigned wide, unsigned high, bool vsync = false, std::string name = "Hello World", bool initNow = true);
	~JNX_Engine();
	bool init(bool vsync = true);

	inline bool isLoaded() const { return loaded; }
	inline bool running() const { return !glfwWindowShouldClose(window); }
	inline unsigned long totalFrameCount() const { return totalFrames; }
	inline void cleanBuffers() const { Renderer::clear(); }
	inline static double time() { return glfwGetTime(); }
	inline size_t numRegisteredObjects() const { return gameObjects.size(); }
	inline ProjectionMode currentProjection() const { return projMode; }
	inline glm::mat4 viewProjection() const { return proj * trans; }
	inline float aspectRatio() const { return static_cast<float>(width) / height; }
	inline static std::string version() { return "0.1b"; }
	inline void setPrintFrameTime(bool val) { printFrameTime = val; }

	void renderGameObject(GameObject* go) const;
	void renderGameObjects();
	void updateGameObjects();

	void setProjectionOrtho(float left, float right, float up, float down);
	void setOrthoCoordsFromCenter(float height);
	void setOrthoCoordsFromTopLeft(float height);
	//FOV needs to be in radians
	inline void setProjectionPerspective(float fov) { setProjectionPerspective(fov, aspectRatio()); }
	//FOV needs to be in radians
	void setProjectionPerspective(float fov, float aspectRatio, float near = Z_NEAR, float far = Z_FAR);
	void setCameraTranslate(const Vec3d& pos);
	void swapBuffers();
	void sortRenderQueue();
	void registerGameObject(GameObject* go);
	void cleanRegisteredGOs(bool deleteCall = true);
};

#endif
