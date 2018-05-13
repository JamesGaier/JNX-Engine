//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//C++ includes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
*/

//Macros
#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCALL(x) gl_clean_errors();\
x;\
ASSERT(gl_check_error(#x, __FILE__, __LINE__))

static void gl_clean_errors() {
	while(glGetError() != GL_NO_ERROR);
}

static bool gl_check_error(const char* func, const char* file, const unsigned int line) {
	bool no_errors = true;
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << std::endl;
		no_errors = false;
	}
	return no_errors;
}

struct ShaderProgramSource {
	std::string vertex, fragment;
};

static ShaderProgramSource parse_shader(const std::string& file_path) {
	std::ifstream input(file_path);
	if(!input) {
		std::cout << "Could not find file " << file_path << std::endl;
		input.close();
	}

	enum class READ_MODE {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream shaders[2];
	READ_MODE current = READ_MODE::NONE;
	while(getline(input, line)) {
		if(line.find("#shader") != std::string::npos) {

			if(line.find("vertex") != std::string::npos) {
				current = READ_MODE::VERTEX;
			} else if(line.find("fragment") != std::string::npos) {
				current = READ_MODE::FRAGMENT;
			}

		} else {
			shaders[static_cast<int> (current)] << line << '\n';

			if(line.find("version") != std::string::npos) {
				if(current == READ_MODE::VERTEX) {
					std::cout << "Vertex shader using GLSL Version " << line.substr(9) << std::endl;
				} else if(current == READ_MODE::FRAGMENT) {
					std::cout << "Fragment shader using GLSL Version " << line.substr(9) << std::endl;
				}
			}
		}
	}

	input.close();

	ShaderProgramSource read_shader = ShaderProgramSource();
	read_shader.fragment = shaders[static_cast<int>(READ_MODE::FRAGMENT)].str();
	read_shader.vertex = shaders[static_cast<int>(READ_MODE::VERTEX)].str();
	return read_shader;
}

static unsigned int compile_shader(unsigned int type, const std::string& source) {

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Error compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl << message << std::endl;
		delete[] message;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int create_shader(const std::string& vertex, const std::string& fragment) {

	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main() {

	/* Initialize the library */
	if(!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK) {
		std::cout << "GLEW init failed!" << std::endl;
	} else {
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GL Shader Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	}


	const unsigned int VERTEX_BUFFER_SIZE = 8;
	const float * const vertex_buffer = new float[VERTEX_BUFFER_SIZE] {
		-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f,
	};

	const unsigned int INDICIES_SIZE = 6;
	const unsigned int* const indicies = new unsigned int[INDICIES_SIZE] {
		0, 1, 2,
			2, 3, 0
	};

	unsigned int vertex_buffer_id;
	GLCALL(glGenBuffers(1, &vertex_buffer_id));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE * sizeof(float), vertex_buffer, GL_STATIC_DRAW));

	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	unsigned int ibo;
	GLCALL(glGenBuffers(1, &ibo));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICIES_SIZE * sizeof(unsigned int), indicies, GL_STATIC_DRAW));

	auto shader_code = parse_shader("res/shaders/basic.shader");
	unsigned int shader = create_shader(shader_code.vertex, shader_code.fragment);
	GLCALL(glUseProgram(shader));

	GLCALL(int location = glGetUniformLocation(shader, "u_Color"));
	ASSERT(location != -1);
	float blue = 0, increment = .005f; //temp
	
	double lastPrint = glfwGetTime();
	int numFrames = 0;
	/* Loop until the user closes the window */
	while(!glfwWindowShouldClose(window)) {

		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
		/* Render here */
		GLCALL(glUniform4f(location, 0.1f, 0.1f, blue, 1.0f));
		blue += increment;
		if(blue >= 1 || blue <= 0) {
			increment = -increment;
		}
		GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		numFrames++;
		if(lastPrint + 1 <= glfwGetTime()) {
			std::cout << 1000.0 / numFrames << "ms per frame" << std::endl;
			numFrames = 0;
			lastPrint += 1;
		}

	}

	glfwTerminate();

	glDeleteProgram(shader);

	delete[] vertex_buffer;

	return 0;
}