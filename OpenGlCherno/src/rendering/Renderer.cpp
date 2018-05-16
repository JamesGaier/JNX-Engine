#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "buffers/IndexBuffer.h"

void Renderer::draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const {
	
	shader->use_program();
	va->Bind();
	ib->Bind();
	GLCALL(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
}

void gl_clean_errors() {
	while(glGetError() != GL_NO_ERROR);
}

bool gl_check_error(const char* func, const char* file, const unsigned int line) {
	bool no_errors = true;
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << std::endl;
		no_errors = false;
	}
	return no_errors;
}
