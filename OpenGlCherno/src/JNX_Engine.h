#ifndef _JNX_ENGINE
#define _JNX_ENGINE

#include "util/Vec3d.h"
#include "rendering/Shader.h"
#include "rendering/Renderer.h"
#include "GameObject.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define Z_NEAR 0.1f
#define Z_FAR 100

enum class ProjectionMode {ORTHO, PERSPECTIVE};

class JNX_Engine {
private:
	GLFWwindow* window;
	Shader* shader;
	Renderer* rend = new Renderer;
	
	bool loaded;
	glm::mat4 proj;
	glm::mat4 trans;

	ProjectionMode projMode;

	double lastPrint = glfwGetTime();
	unsigned numFrames;
	unsigned lastFPS;
	unsigned long totalFrames;
public:
	JNX_Engine(bool initNow = true);
	~JNX_Engine();
	bool init(bool vsync = true);
	
	inline bool isLoaded() const { return loaded; }
	inline bool running() const { return !glfwWindowShouldClose(window); }
	inline unsigned long totalFrameCount() const { return totalFrames; }
	inline void cleanBuffers() const { rend->clear(); }
	inline glm::mat4 viewProjection() const { return proj * trans; }
	inline glm::mat4 mvp(GameObject* go) const { return viewProjection() * go->getModelMatrix(); }
	inline Shader* shaderManip() { return shader; }
	void renderGameObject(GameObject* go) const;

	void setProjectionOrtho( float left, float right, float up, float down, float near = Z_NEAR, float far = Z_FAR);
	//FOV needs to be in radians
	void setProjectionPerspective(float fov, float aspectRatio, float near = Z_NEAR, float far = Z_FAR);
	void setCameraTranslate(const Vec3d& pos);
	void loadShader(const std::string& file);
	void swapBuffers();
};

#endif