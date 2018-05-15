#include "Renderer.h"

void gl_clean_errors() {
	while(glGetError() != GL_NO_ERROR);
}

bool gl_check_error(const char* func, const char* file, const unsigned int line) {
	bool no_errors = true;
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << std::endl;
		no_errors = false;
	}
	return no_errors;
}
