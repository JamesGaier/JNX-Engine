#ifndef _RENDERER
#define _RENDERER

#include "buffers/IndexBuffer.h"
#include "buffers/VertexBuffer.h"
#include "Shader.h"
#include "Model.h"
#include <GL/glew.h>

//To Consider: Renderer may not need to be a class
class Renderer {

public:
	inline void clear() const { GLCALL(glClear(GL_COLOR_BUFFER_BIT)); }
	void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
	void draw(const Model* m, const Shader* shader) const;
};

#endif // !_RENDERER

