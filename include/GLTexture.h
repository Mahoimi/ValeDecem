#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <string>
#include <GL/glew.h>
#include <vector>

/*!
* \class GLTexture
* Store an image in an OpenGL texture
*/
class GLTexture {
private:
	GLuint m_textureID;

    // We don't want an unexpected copy of an instance of this class
    GLTexture(const GLTexture& texture);
    GLTexture& operator=(const GLTexture& texture);

public:
	// Constructor of GLTexture class
	GLTexture();

	// Destructor of GLTexture class
    ~GLTexture();

	// Load an image into an OpenGL texture
    void load(const std::string& imagepath);

    // Bind the OpenGL texture to the designated texture unit
    void bind(const GLenum textureUnit) const;
};

#endif // GLTEXTURE_h
