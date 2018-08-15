#include "Texture.h"
#include "stb_image/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path, bool keepLocal) :
	m_path(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0), m_kept(keepLocal) {
	stbi_set_flip_vertically_on_load(1);

	m_localBuffer = stbi_load(m_path.c_str(), &m_width, &m_height, &m_BPP, 4);

	GLCALL(glGenTextures(1, &m_ID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_ID));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	Unbind();

	if(m_localBuffer && !m_kept) stbi_image_free(m_localBuffer);
}

Texture::~Texture() {
	GLCALL(glDeleteTextures(1, &m_ID));
	if(m_kept) delete[] m_localBuffer;
}

void Texture::Bind(unsigned slot) const {
	if(slot >= 32) {
		std::cerr << "Texture slot #" << slot << " does not exist in OpenGL!" << std::endl;
	}

	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_ID));
}
