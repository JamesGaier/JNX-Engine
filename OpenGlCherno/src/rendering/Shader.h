#ifndef _SHADER
#define _SHADER

#include <string>

struct ShaderProgramSource {
	std::string vertex, fragment;
};

class Shader {
private:
	unsigned m_shaderID;

	ShaderProgramSource* parse_shader(const std::string& file_path);
	unsigned compile_shader(unsigned int type, const std::string& source);
	unsigned create_shader(const ShaderProgramSource* source);
public:
	Shader(const std::string& filename);
	~Shader();

	void use_program() const;
	int uniform_location(const char* name) const;

	void setUniform4f(const int& location, const float& a, const float& b, const float& c, const float& d) const;

	inline unsigned renderer_id() const { return m_shaderID; }
};

#endif