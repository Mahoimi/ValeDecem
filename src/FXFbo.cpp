#include <FXFbo.h>
#include <cassert>

void FXFbo::init(const unsigned int width, const unsigned int height){
    // Generate the three textures we need
    glGenTextures(4, m_textures);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);

    // Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    // Define the filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_textures[1]);

    // Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    // Define the filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_textures[2]);

    // Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width/2, height/2, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    // Define the filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, m_textures[3]);

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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, m_textures[0], 0);

    // Verify FrameBuffer
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    // Debind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FXFbo::bindFramebufferWith(unsigned int index) {
    // Bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, m_textures[index], 0);
}

const GLuint& FXFbo::getTexture(unsigned int index) {
    assert(index < 4);
    return m_textures[index];
}

FXFbo::~FXFbo(){
    // Free the memory
    glDeleteTextures(4, m_textures);
    glDeleteFramebuffers(1, &m_framebuffer);
}
