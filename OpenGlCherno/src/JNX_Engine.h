#ifndef _JNX_ENGINE
#define _JNX_ENGINE

#include "util/Vec3d.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define Z_NEAR 0.1f
#define Z_FAR 100

enum class ProjectionMode {ORTHO, PERSPECTIVE};

class JNX_Engine {
private:
	GLFWwindow* window;
	bool loaded;
	glm::mat4 proj;
	glm::mat4 trans;

	ProjectionMode projMode;
public:
	JNX_Engine(bool initNow = false);
	~JNX_Engine();
	bool init(bool vsync = true);
	
	inline bool isLoaded() const { return loaded; }
	inline bool running() const { return !glfwWindowShouldClose(window); }
	inline void swapBuffers() const { glfwSwapBuffers(window); }
	inline glm::mat4 viewProjection() const { return proj * trans; }

	void setProjectionOrtho( float left, float right, float up, float down, float near = Z_NEAR, float far = Z_FAR);
	void setProjectionPerspective(float fov, float aspectRatio, float near = Z_NEAR, float far = Z_FAR);
	void setCameraTranslate(const Vec3d& pos);
};

#endif