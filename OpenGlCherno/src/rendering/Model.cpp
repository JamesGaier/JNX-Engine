#include "Model.h"

#include "obj_loader/OBJ_Loader.h"


Model::Model(const std::string & file, bool is3D) : is3D(is3D) {

	if(file != EMPTY_MODEL_SOURCE) {
		loadModel(file);
	}
}

Model::~Model() { cleanData(); }

bool Model::loadModel(const std::string & file, bool is3D) {
	
	objl::Loader loader;

	if(loader.LoadFile(file)) {
		cleanData();

		VERTEX_BUFFER_COUNT = loader.LoadedVertices.size() * (2 + is3D);
		vertex_buffer = new float[VERTEX_BUFFER_COUNT];

		int currentIndex = 0;
		for(unsigned i = 0; i < loader.LoadedVertices.size(); i++) {
			objl::Vector3 data = loader.LoadedVertices[i].Position;
			vertex_buffer[currentIndex] = data.X;
			vertex_buffer[currentIndex + 1] = data.Y;
			vertex_buffer[currentIndex + 2] = data.Z;
			currentIndex += 3;
		}

		INDICE_COUNT = loader.LoadedIndices.size();
		indicies = new unsigned int[INDICE_COUNT];

		for(unsigned i = 0; i < loader.LoadedIndices.size(); i++) {
			*(indicies + i) = loader.LoadedIndices[i];
		}

		std::cout << "Successfully loaded " << file << std::endl;

		this->is3D = is3D;
		genBuffers();

		return true;
	} else {
		return false;
	}
}

bool Model::loadSquare(float sideLength) {
	if(sideLength == 0) {
		return false;
	}
	
	cleanData();

	float halfSide = sideLength / 2;

	VERTEX_BUFFER_COUNT = 8;
	vertex_buffer = new float[VERTEX_BUFFER_COUNT] {
		-halfSide, -halfSide,
		halfSide, -halfSide,
		halfSide, halfSide,
		-halfSide, halfSide
	};

	INDICE_COUNT = 6;
	indicies = new unsigned int[INDICE_COUNT] {
		0, 1, 2,
			2, 3, 0
	};

	genBuffers();

	return true;
}

void Model::cleanData() { 
	delete[] vertex_buffer; 
	delete[] indicies; 
	delete ib;
	delete vb;
}

void Model::genBuffers() {

	vb = new VertexBuffer(vertex_buffer, VERTEX_BUFFER_COUNT * sizeof(float));
	VertexBufferLayout* vbl = new VertexBufferLayout;
	vbl->push<float>(2 + is3D);

	va = new VertexArray;
	va->addBuffer(vb, vbl);

	ib = new IndexBuffer(indicies, INDICE_COUNT);

}
