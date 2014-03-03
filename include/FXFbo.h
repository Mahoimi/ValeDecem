#ifndef FXFBO_H
#define FXFBO_H

#include <GL/glew.h>

class FXFbo{
private :
    GLuint m_framebuffer;
    GLuint m_colorTexture;
    GLuint m_drawbuffer;

    // We don't want an unexpected copy of an instance of this class
    FXFbo(const FXFbo&);
    FXFbo& operator=(const FXFbo&);

public :
    FXFbo(){}
    void init(const unsigned int width, const unsigned int height);
    void bindFramebuffer() const;
    const GLuint& getTexture() const;
    ~FXFbo();
};

#endif // FXFbo_H
