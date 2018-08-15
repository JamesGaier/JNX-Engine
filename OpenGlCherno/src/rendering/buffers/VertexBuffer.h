#ifndef _VERTEX_BUFFER
#define _VERTEX_BUFFER
/*
* Purpose: easy handle for the OpenGL VertexBuffer
* @author Nicholas Baron
*/
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
