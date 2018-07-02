#include"Input.h"
/*
* see .h file for documentation
*/
double Input::getMouseX() const {
	return mouseX;
}
double Input::getMouseY() const {
	return mouseY;
}
void Input::update(GLFWwindow* win) {
	glfwGetCursorPos(win, &mouseX, &mouseY);
}
void Input::setMousePosition(GLFWwindow* win, double x, double y) {
	glfwSetCursorPos(win, x,y);
}