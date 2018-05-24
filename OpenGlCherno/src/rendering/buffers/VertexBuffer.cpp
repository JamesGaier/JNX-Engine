#include "VertexBuffer.h"
#include "../Renderer.h"

VertexBuffer::VertexBuffer(const void* data, const unsigned int size) {

	GLCALL(glGenBuffers(1, &m_rendererID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCALL(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::Bind() const {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}