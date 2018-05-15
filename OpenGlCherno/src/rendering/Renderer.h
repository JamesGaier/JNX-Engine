#ifndef _RENDERER
#define _RENDERER

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCALL(x) gl_clean_errors();\
x;\
ASSERT(gl_check_error(#x, __FILE__, __LINE__))

void gl_clean_errors();

bool gl_check_error(const char* func, const char* file, const unsigned int line);

#endif // !_RENDERER

