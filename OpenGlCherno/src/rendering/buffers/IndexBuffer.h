#ifndef _INDEX_BUFFER
#define _INDEX_BUFFER

class IndexBuffer {
private:
	unsigned m_rendererID;
	unsigned m_count;
public:
	IndexBuffer(unsigned* data, unsigned count);
	~IndexBuffer();

	void Bind() const;
	inline void Unbind() const;

	inline unsigned getCount() const { return m_count; }
};

#endif