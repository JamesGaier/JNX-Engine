#include "Input.h"
/*
* see .h file for documentation
*/

double Input::mouseX, Input::mouseY;
std::unordered_map<unsigned char, bool> Input::downKeys;

std::vector<char> Input::downNow() {
	std::vector<char> toRet;

	for(auto iter = downKeys.begin(); iter != downKeys.end(); iter++) {
		if(iter->second) {
			toRet.push_back(iter->first);
		}
	}

	return toRet;
}

void Input::setMousePosition(GLFWwindow* win, double x, double y) {
	glfwSetCursorPos(win, x, y);
}

void Input::cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
	mouseX = xpos;
	mouseY = ypos;
}

void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if((mods & GLFW_MOD_SHIFT) == 0) {
		key += 0x20; //Make non-shift keys lowercase
	}
	
	if(action == GLFW_PRESS) {
		downKeys[key] = true;
	} else if(action == GLFW_RELEASE) {
		downKeys[key] = false;
	}
}
