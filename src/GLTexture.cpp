#include <GLTexture.h>
#include <cassert>
#include <SFML/Graphics/Image.hpp>


GLTexture::GLTexture(): m_textureID(0){
        
}

void GLTexture::load(const std::string& imagepath) {
	assert(imagepath.length() > 0);

	// Create one OpenGL texture
	glGenTextures(1, &m_textureID);

	// Create a loader for the image with SFML
	sf::Image image;
		
	// Check if the image has been loaded
	assert(image.loadFromFile(imagepath));

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_textureID);

		// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

		// Trilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
			
	glBindTexture(GL_TEXTURE_2D, 0);

	assert(glIsTexture(m_textureID) == GL_TRUE);
}

void GLTexture::bind(const GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLTexture::~GLTexture(){
    // Delete the texture
	if (glIsTexture(m_textureID) == GL_TRUE) glDeleteTextures(1, &m_textureID);
}
