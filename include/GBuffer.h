#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL/glew.h>

class GBuffer {
private:
	GLuint m_framebuffer;
	GLuint m_textures[3];
	GLuint m_drawbuffers[2];

	// We don't want an unexpected copy of an instance of this class
    GBuffer(const GBuffer&);
    GBuffer& operator=(const GBuffer&);

public:
	GBuffer(){}
	void init(unsigned int width, unsigned int height);
	void bindFramebuffer() const;
	void bindTextures() const;
	const GLuint& getTexture(unsigned int index) const;
	~GBuffer();
};

#endif // GBUFFER_H