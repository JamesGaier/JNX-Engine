#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "../util/GLUtil.h"

void Renderer::draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) {
	shader->use_program();
	va->Bind();
	ib->Bind();
	GLCALL(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const Model* m, const Shader* shader) {
	draw(m->vertexArray(), m->indexBuffer(), shader);
}
