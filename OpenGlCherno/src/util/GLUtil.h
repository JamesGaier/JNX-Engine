#ifndef _GLUTIL
#define _GLUTIL

#include <GL/glew.h>
#include <iostream>
#include <string_view>

#define ASSERT(x) if(!(x)) __debugbreak()

#define GLCALL(x) gl_clean_errors();x;\
ASSERT(gl_check_error(#x, __FILE__, __LINE__))
/*
* Purpose: helper methods for OpenGL
* @author Nicholas Baron
*/
inline void gl_clean_errors() { while(glGetError() != GL_NO_ERROR); }

inline bool gl_check_error(std::string_view func, std::string_view file, const unsigned line) {
	auto no_errors = true;
	while(auto error = glGetError()) {
		using namespace std;
		cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << endl;
		cout << glewGetErrorString(error) << endl;
		no_errors = false;
	}
	return no_errors;
}

#endif // !_GLUTIL
