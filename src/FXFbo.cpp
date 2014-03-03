#include <FXFbo.h>
#include <cassert>

void FXFbo::init(const unsigned int width, const unsigned int height){
    // Generate the three textures we need
    glGenTextures(1, &m_colorTexture);

    // Bind the color texture
    glBindTexture(GL_TEXTURE_2D, m_colorTexture);

    // Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, m_colorTexture, 0);
    m_drawbuffer = GL_COLOR_ATTACHMENT0;

    // Verify FrameBuffer
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    // Debind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FXFbo::bindFramebuffer() const {
    // Bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    // Specify how many buffers we use
    glDrawBuffers(1, &m_drawbuffer);
}

const GLuint& FXFbo::getTexture() const {
    return m_colorTexture;
}

FXFbo::~FXFbo(){
    // Free the memory
    glDeleteTextures(1, &m_colorTexture);
    glDeleteFramebuffers(1, &m_framebuffer);
}
