#ifndef _RENDERER
#define _RENDERER

#include "buffers/IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Model.h"
#include <GL/glew.h>
/*
* Purpose: central file for rendering methods
* @author Nicholas Baron
*/

namespace Renderer {

	inline void clear() { GLCALL(glClear(GL_COLOR_BUFFER_BIT)); }
	void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader);
	void draw(const Model* m, const Shader* shader);
};

#endif // !_RENDERER
