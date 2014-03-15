#include <ShadowMap.h>
#include <cassert>

void ShadowMap::init(unsigned int width, unsigned int height){
    // Generate the texture we need
    glGenTextures(1, &m_texture);

    // Bind the depth texture
    glBindTexture(GL_TEXTURE_2D,m_texture);

    // Define the depth texture
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture, 0);

	// Verify FrameBuffer
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	// Debind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ShadowMap::bindFramebuffer() const {
	// Bind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

const GLuint& ShadowMap::getTexture() const {
    return m_texture;
}

ShadowMap::~ShadowMap(){
	// Free the memory
    glDeleteTextures(1, &m_texture);
	glDeleteFramebuffers(1, &m_framebuffer);
}
