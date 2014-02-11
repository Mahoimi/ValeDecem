#include <GBuffer.h>
#include <cassert>

void GBuffer::init(unsigned int width, unsigned int height){
	// Generate the three textures we need
	glGenTextures(3, m_textures);

	// Bind the color texture
	glBindTexture(GL_TEXTURE_2D,m_textures[0]);

	// Define the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Define the filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Bind the color texture
    glBindTexture(GL_TEXTURE_2D, m_textures[1]);

	// Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Define the filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Bind the depth texture
    glBindTexture(GL_TEXTURE_2D, m_textures[2]);

	// Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	// Define the filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	 // Create Framebuffer Object
	glGenFramebuffers(1, &m_framebuffer);

	// Bind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// Attach textures to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, m_textures[0], 0);
	m_drawbuffers[0] = GL_COLOR_ATTACHMENT0;
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1 , GL_TEXTURE_2D, m_textures[1], 0);
	m_drawbuffers[1] = GL_COLOR_ATTACHMENT1;
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_textures[2], 0);

	// Verify FrameBuffer
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	// Debind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GBuffer::bindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

void GBuffer::bindTextures() const {
	glActiveTexture(m_drawbuffers[0]);
	glBindTexture(GL_TEXTURE_2D, m_textures[0]);

	glActiveTexture(m_drawbuffers[1]);
	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
}

GBuffer::~GBuffer(){
	// Free the memory
	glDeleteTextures(3, m_textures);
	glDeleteFramebuffers(1, &m_framebuffer);
}