#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

#include <GL/glew.h>
#include <string>

/*!
* \class CubemapTexture
*  Store six images in a cubemap texture
*/
class CubemapTexture {
private:
    GLuint m_textureID;

    // We don't want an unexpected copy of an instance of this class
    CubemapTexture(const CubemapTexture& cubemap);
    CubemapTexture& operator=(const CubemapTexture& cubemap);

public:
    CubemapTexture();
    ~CubemapTexture();

    // Load six images into a cubemap texture
    void load(const std::string& directoryPath,
              const std::string& posXPath,
              const std::string& negXPath,
              const std::string& posYPath,
              const std::string& negYPath,
              const std::string& posZPath,
              const std::string& negZPath);

    // Bind the cubemap texture to the designated texture unit
    void bind(const GLenum textureUnit) const;

};

#endif // CUBEMAPTEXTURE_H
