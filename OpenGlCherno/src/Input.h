#ifndef _H_INPUT_
#define _H_INPUT_
/* 
*	Purpose: gets and processes mouse input
*	@author James Gaier
*/
class Input {
private:
	int mouseX, mouseY;
public:
	int getMouseX() const;
	int getMouseY() const;
	void update();
	void setMousePosition(int x, int y);
};
#endif