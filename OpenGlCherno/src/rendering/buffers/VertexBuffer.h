#ifndef _VERTEX_BUFFER
#define _VERTEX_BUFFER

class VertexBuffer {
private:
	unsigned m_rendererID;
public:
	//Size means you use sizeof in the parameter
	VertexBuffer(void* data, unsigned size);
	~VertexBuffer();

	void Bind() const;
	inline void Unbind() const;
};

#endif