#ifndef _H_INPUT_
#define _H_INPUT_

#include "util/Vec3d.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
/*
*	Purpose: gets and processes input
*	@author James Gaier
*/
class Input {
private:
	static double mouseX, mouseY;
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	static std::unordered_map<unsigned char, bool> downKeys;
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	inline static double getMouseX() { return mouseX; }
	inline static double getMouseY() { return mouseY; }
	inline static Vec3d mousePos() { return Vec3d(mouseX, mouseY, 0); }

	inline static bool isDown(unsigned char c) { return downKeys[c]; }
	static std::vector<char> downNow();

	static void setMousePosition(GLFWwindow* win, double x, double y);
	inline static void registerAsCallback(GLFWwindow* win) { 
		glfwSetKeyCallback(win, &Input::key_callback); 
		glfwSetCursorPosCallback(win, &Input::cursor_position_callback);
	}
};
#endif
