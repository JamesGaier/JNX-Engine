#ifndef _VERTEX_ARRAY
#define _VERTEX_ARRAY

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"
/*
* Purpose: allows for more complex vertex data
* @author Nicholas Baron
*/
class VertexArray {
private:
	unsigned m_rendererID;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);
	inline void Bind() const;
	inline void Unbind() const;
};

#endif