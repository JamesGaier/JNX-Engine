#include "Model.h"

#include "obj_loader/OBJ_Loader.h"

inline float magnitude(objl::Vector3 vec) {
	return sqrtf((vec.X * vec.X) + (vec.Y * vec.Y) + (vec.Z * vec.Z));
}

Model::Model(const std::string & file, bool is3D) : is3D(is3D) {
	normalFactor = 1;
	if(file != EMPTY_MODEL_SOURCE) {
		loadModel(file);
		std::cout << "Vertices loaded: " << VERTEX_BUFFER_COUNT << std::endl;
		std::cout << "Indices loaded: " << INDICE_COUNT << std::endl;
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
		float farthestVertex = 0;
		for(unsigned i = 0; i < loader.LoadedVertices.size(); i++) {
			objl::Vector3 data = loader.LoadedVertices[i].Position;
			vertex_buffer[currentIndex] = data.X;
			vertex_buffer[currentIndex + 1] = data.Y;
			vertex_buffer[currentIndex + 2] = data.Z;
			
			if(magnitude(data) > farthestVertex) {
				farthestVertex = magnitude(data);
			}

			currentIndex += 3;
		}
		normalFactor = 1 / farthestVertex;

		INDICE_COUNT = loader.LoadedIndices.size();
		indicies = new unsigned int[INDICE_COUNT];

		for(unsigned i = 0; i < loader.LoadedIndices.size(); i++) {
			*(indicies + i) = loader.LoadedIndices[i];
		}

		this->is3D = is3D;
		genBuffers();

		std::cout << "Successfully loaded " << file << std::endl;
		return true;
	} else { std::cerr << "File " << file << " could not be loaded" << std::endl; }
	
	return false;
}

bool Model::loadSquare(float sideLength) {
	if(sideLength <= 0) {
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
	delete va;
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
