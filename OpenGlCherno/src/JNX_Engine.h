#ifndef _JNX_ENGINE
#define _JNX_ENGINE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class JNX_Engine {
private:
	GLFWwindow* window;
	bool loaded;
public:
	JNX_Engine(bool initNow = false);
	~JNX_Engine();
	bool init(bool vsync = true);
	
	inline bool isLoaded() const { return loaded; }
	inline bool running() const { return !glfwWindowShouldClose(window); }
	inline void swapBuffers() const { glfwSwapBuffers(window); }
};

#endif