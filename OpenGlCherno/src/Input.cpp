#include"Input.h"
#include<GLFW/glfw3.h>
/*
* see .h file for documentation
*/
int Input::getMouseX() const {
	return mouseX;
}
int Input::getMouseY() const {
	return mouseY;
}
void Input::update() {
	glfwGetMousePos(&mouseX, &mouseY);
}
void Input::setMousePosition(int x, int y) {
	glfwSetMousePos(x,y);
}