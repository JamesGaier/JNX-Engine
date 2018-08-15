#ifndef _GLUTIL
#define _GLUTIL

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak()

#define GLCALL(x) gl_clean_errors();\
x;\
ASSERT(gl_check_error(#x, __FILE__, __LINE__))
/*
* Purpose: helper methods for OpenGL
* @author Nicholas Baron
*/
inline void gl_clean_errors() { while(glGetError() != GL_NO_ERROR); }

inline bool gl_check_error(const char* func, const char* file, const unsigned line) {
	bool no_errors = true;
	while(auto error = glGetError()) {
		std::cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << std::endl;
		std::cout << glewGetErrorString(error) << std::endl;
		no_errors = false;
	}
	return no_errors;
}

#endif // !_GLUTIL
