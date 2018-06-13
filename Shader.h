#ifndef _H_SHADER_
#define _H_SHADER_
#include<string>
#include<unordered_map>
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader {
private:
	std::string m_FilePath;
	unsigned m_RendererID;
	std::unordered_map<std::string, unsigned> m_UniformLocationCache;
public:
	Shader(const std::string& filePath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	//set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	unsigned GetUniformLocation(const std::string& name);
	unsigned Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
	unsigned CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string & filePath);
};

#endif
