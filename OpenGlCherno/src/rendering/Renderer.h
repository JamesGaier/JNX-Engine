#ifndef _RENDERER
#define _RENDERER

#define ASSERT(x) if(!(x)) __debugbreak()
//Assert needs to be here for the other includes

#include <GL/glew.h>
#include <iostream>
#include "buffers/IndexBuffer.h"

#define GLCALL(x) gl_clean_errors();\
x;\
ASSERT(gl_check_error(#x, __FILE__, __LINE__))

void gl_clean_errors();

bool gl_check_error(const char* func, const char* file, const unsigned int line);

//Forwards declarations
class VertexArray;
class Shader;

//To Consider: Renderer may not need to be a class
class Renderer {

public:
	inline void clear() const { GLCALL(glClear(GL_COLOR_BUFFER_BIT)); }
	void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
};

#endif // !_RENDERER

