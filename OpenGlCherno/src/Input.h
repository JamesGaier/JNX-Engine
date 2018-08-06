#ifndef _H_INPUT_
#define _H_INPUT_

#include <GLFW/glfw3.h>

/* 
*	Purpose: gets and processes input
*	@author James Gaier
*/
class Input {
private:
	double mouseX, mouseY;
public:
	double getMouseX() const;
	double getMouseY() const;
	void update(GLFWwindow* win);
	void setMousePosition(GLFWwindow* win, double x, double y);
};
#endif