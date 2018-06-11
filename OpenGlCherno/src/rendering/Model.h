#ifndef _MODEL
#define _MODEL

#include "buffers/VertexBuffer.h"
#include "VertexArray.h"
#include "buffers/IndexBuffer.h"

#include <string>

#define EMPTY_MODEL_SOURCE "NONE"

class Model {
private:
	bool is3D;
	
	unsigned int VERTEX_BUFFER_COUNT;
	float* vertex_buffer;

	unsigned int INDICE_COUNT;
	unsigned int* indicies;

	VertexBuffer* vb;
	VertexArray* va;
	IndexBuffer* ib;

	void cleanData();
	void genBuffers();

public:
	Model(const std::string& file = EMPTY_MODEL_SOURCE, bool is3D = false);
	~Model();

	inline VertexArray* vertexArray() const { return va; }
	inline IndexBuffer* indexBuffer() const { return ib; }

	bool loadModel(const std::string& file, bool is3D = true);
	bool loadSquare(float sideLength);
};

#endif // !_MODEL