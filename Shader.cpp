#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include"renderer.h"
#include<sstream>

Shader::Shader(const std::string& filePath) : m_FilePath(filePath), m_RendererID(0) {
	ShaderProgramSource source = ParseShader(filePath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}
Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
}
void Shader::Bind() const {
	GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const {
	GLCall(glUseProgram(0));
}
//set uniforms
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
unsigned Shader::GetUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}
	GLCall(unsigned location = glGetUniformLocation(m_RendererID,name.c_str()));
	if (location == -1)
		std::cout << "Warning uniform " << name << " does not exist" << std::endl;
		m_UniformLocationCache[name] = location;
	return location;
}
unsigned Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader) {
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
	return program;

}
 unsigned Shader::CompileShader(unsigned int type, const std::string& source) {
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "FAILED TO COMPILE" << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << "SHADER" << std::endl;
		std::cout << message;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

ShaderProgramSource Shader::ParseShader(const std::string & filePath) {
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}

			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}

		}
		else {
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(),ss[1].str() };
}
