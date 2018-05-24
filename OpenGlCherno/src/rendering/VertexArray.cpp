#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray() {
	GLCALL(glGenVertexArrays(1, &m_rendererID));
	GLCALL(glBindVertexArray(m_rendererID));
}


VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout) {

	Bind();
	vb->Bind();
	const auto& elements = layout->elements();
	unsigned offset = 0;

	for(unsigned i = 0; i < elements.size(); i++) {

		const auto e = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, e.count, e.type, e.normalized ? GL_TRUE : GL_FALSE, layout->stride(), (const void*)offset));

		offset += e.count * VertexElement::sizeOfType(e.type);
	}

}

void VertexArray::Bind() const {
	GLCALL(glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind() const {
	GLCALL(glBindVertexArray(0));
}
