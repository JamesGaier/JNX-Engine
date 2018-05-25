#ifndef _TEXTURE
#define _TEXTURE

#include "../util/GLUtil.h"

class Texture {
private:
	unsigned m_ID;
	std::string m_path;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_BPP;
	bool m_kept;
public:
	Texture(const std::string& path, bool keepLocal = false);
	~Texture();

	void Bind(unsigned slot = 0) const;
	inline void Unbind() const { GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); }

	inline unsigned width() const { return m_width; }
	inline unsigned height() const { return m_width; }
};

#endif
