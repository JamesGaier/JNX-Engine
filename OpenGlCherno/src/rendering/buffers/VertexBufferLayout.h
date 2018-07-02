#ifndef _VERTEX_BUFFER_LAYOUT
#define _VERTEX_BUFFER_LAYOUT

#include "../util/GLUtil.h"
#include <vector>
/*
* Purpose: custom vertex data
* @author Nicholas Baron
*/
struct VertexElement {
	unsigned type;
	unsigned count;
	bool normalized;

	static unsigned sizeOfType(unsigned type) {
	
		switch(type) {
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexElement> m_elements;
	unsigned m_stride = 0;
public:
	template<typename T>
	void push(unsigned count) {
		static_assert(false);
	}

	template<>
	void push<float>(unsigned count) {

		m_elements.push_back({GL_FLOAT, count, false});
		m_stride += VertexElement::sizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned>(unsigned count) {

		m_elements.push_back({GL_UNSIGNED_INT, count, false});
		m_stride += VertexElement::sizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(unsigned count) {

		m_elements.push_back({GL_UNSIGNED_BYTE, count, true});
		m_stride += VertexElement::sizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexElement>& elements() const { return m_elements; }
	inline unsigned stride() const { return m_stride; }
};

#endif