#include "IndexBuffer.h"
#include "../util/GLUtil.h"

IndexBuffer::IndexBuffer(const unsigned* data, const unsigned count) : m_count(count) {

	ASSERT(sizeof(unsigned) == sizeof(GLuint));

	GLCALL(glGenBuffers(1, &m_rendererID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCALL(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::Bind() const {
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::Unbind() const {
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}