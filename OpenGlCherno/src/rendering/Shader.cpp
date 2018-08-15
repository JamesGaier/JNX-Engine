#include "Shader.h"
#include "../util/GLUtil.h"
#include "../util/TextUtil.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

Shader::Shader(const std::string& filename) {
	auto source = parse_shader(filename);
	m_shaderID = create_shader(source);
	delete source;

	std::cout << "Shader created from " << filename << std::endl;
}

int Shader::uniform_location(const std::string& name) {
	auto got = uniformCache.find(name);

	if(got != uniformCache.end()) {
		return got->second;
	}

	GLCALL(int location = glGetUniformLocation(m_shaderID, name.c_str()));
	ASSERT(location != -1);

	uniformCache[name] = location;

	return location;
}

void Shader::setUniform1f(const std::string & name, float val) {
	GLCALL(glUniform1f(uniform_location(name), val));
}

void Shader::setUniform1i(const std::string & name, int val) {
	GLCALL(glUniform1i(uniform_location(name), val));
}

void Shader::setUniform4f(const std::string& name, float a, float b, float c, float d) {
	GLCALL(glUniform4f(uniform_location(name), a, b, c, d));
}

void Shader::setUniformMat4f(const std::string & name, const glm::mat4 & matrix) {
	GLCALL(glUniformMatrix4fv(uniform_location(name), 1, GL_FALSE, &matrix[0][0]));
}

ShaderProgramSource* Shader::parse_shader(const std::string& file_path) {
	std::vector<std::string> shaderText;
	if(!loadTextFromFile(file_path, shaderText)) {
		std::cerr << "Could not find file " << file_path << std::endl;
		throw "SHADER NOT FOUND";
	}

	enum READ_MODE {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	} current = READ_MODE::NONE;

	std::stringstream shaders[2];
	for each (const std::string& line in shaderText) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") != std::string::npos) {
				current = READ_MODE::VERTEX;
			} else if(line.find("fragment") != std::string::npos) {
				current = READ_MODE::FRAGMENT;
			}
		} else {
			shaders[static_cast<int> (current)] << line << std::endl;

			if(line.find("version") != std::string::npos) {
				if(current == READ_MODE::VERTEX) {
					std::cout << "Vertex shader using GLSL Version " << line.substr(9) << std::endl;
				} else if(current == READ_MODE::FRAGMENT) {
					std::cout << "Fragment shader using GLSL Version " << line.substr(9) << std::endl;
				}
			}
		}
	}

	auto read_shader = new ShaderProgramSource;
	read_shader->fragment = shaders[READ_MODE::FRAGMENT].str();
	read_shader->vertex = shaders[READ_MODE::VERTEX].str();
	return read_shader;
}

unsigned Shader::compile_shader(unsigned type, const std::string& source) {
	auto id = glCreateShader(type);

	/*
	This points to the same section of data as the source string.
	It will be deleted with the struct.
	*/
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		auto message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cerr << "Compilation error in the " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl << message << std::endl;
		delete[] message;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned Shader::create_shader(const ShaderProgramSource* source) {
	auto program = glCreateProgram();
	auto vs = compile_shader(GL_VERTEX_SHADER, source->vertex);
	auto fs = compile_shader(GL_FRAGMENT_SHADER, source->fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
