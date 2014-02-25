#include <CubemapTexture.h>
#include <cassert>
#include <SFML/Graphics/Image.hpp>

static const GLenum types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };


CubemapTexture::CubemapTexture(): m_textureID(0){

}


void CubemapTexture::load(const std::string& directoryPath,
                          const std::string& posXPath,
                          const std::string& negXPath,
                          const std::string& posYPath,
                          const std::string& negYPath,
                          const std::string& posZPath,
                          const std::string& negZPath){


    // Cheking if the directory name has a / at the end
    std::string::const_iterator it = directoryPath.end();
    it--;
    std::string directory = (*it == '/') ? directoryPath : directoryPath + "/";


    std::string imagePath[6];
    imagePath[0] = directory + posXPath;
    imagePath[1] = directory + negXPath;
    imagePath[2] = directory + posYPath;
    imagePath[3] = directory + negYPath;
    imagePath[4] = directory + posZPath;
    imagePath[5] = directory + negZPath;

    // Create one OpenGL texture
    glGenTextures(1, &m_textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

        for (unsigned int i = 0 ; i < 6 ; ++i) {

            assert(imagePath[i].length() > 0);

            // Create a loader for the images with SFML
            sf::Image image;

            // Check if the image has been loaded
            assert(image.loadFromFile(imagePath[i]));

            // Give the image to OpenGL
            glTexImage2D(types[i], 0, GL_RGB, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void CubemapTexture::bind(const GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
}

CubemapTexture::~CubemapTexture(){
    // Delete the texture
    if (glIsTexture(m_textureID) == GL_TRUE) glDeleteTextures(1, &m_textureID);
}

