#ifndef SHADOWMAP_H
#define ShadowMap_H

#include <GL/glew.h>

/*!
* \class ShadowMap
* Handle the Framebuffer used for the shadow mapping
*/
class ShadowMap {
private:
	GLuint m_framebuffer;
    GLuint m_texture;

	// We don't want an unexpected copy of an instance of this class
    ShadowMap(const ShadowMap&);
    ShadowMap& operator=(const ShadowMap&);

public:
    ShadowMap(){}
	void init(unsigned int width, unsigned int height);
	void bindFramebuffer() const;
    const GLuint& getTexture() const;
    ~ShadowMap();
};

#endif // SHADOWMAP_H
