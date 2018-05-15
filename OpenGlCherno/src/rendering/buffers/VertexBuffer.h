#ifndef _VERTEX_BUFFER
#define _VERTEX_BUFFER

class VertexBuffer {
private:
	unsigned int m_rendererID;
public:
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();

	void Bind() const;
	inline void Unbind() const;
};

#endif