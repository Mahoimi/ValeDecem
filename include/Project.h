#ifndef PROJECT_H
#define PROJECT_H

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Cube.h>
#include <Plane.h>
#include <GLProgram.h>
#include <FreeFlyCamera.h>
#include <GLTexture.h>
#include <GBuffer.h>

class Project {
private:
	sf::Window m_window;

	Cube m_cube;
	Plane m_floorPlane;
	Plane m_blitPlane;
	GLTexture m_diffuseTexture;
	GLTexture m_specularTexture;
	FreeFlyCamera m_camera;
	GBuffer m_gbuffer;

	struct GBufferGLSL {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_projectionLocation;
		GLuint m_diffuseLocation;
		GLuint m_specularLocation;
		GLProgram m_program;

		GBufferGLSL(){}
	};
	GBufferGLSL m_gbufferGLSL;

	struct BlitGLSL {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_projectionLocation;
		GLuint m_textureLocation;
		GLProgram m_program;

		BlitGLSL(){}
	};
	BlitGLSL m_blitGLSL;

	struct ShadingGLSL {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightPositionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
		GLProgram m_program;

		ShadingGLSL(){}
	};
	ShadingGLSL m_shadingGLSL;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	sf::Vector2i m_mousePosition;
	sf::Vector2i m_prevMousePosition;

	void getInput();
	void gBufferPass();
	void shadingPass();
	void blitPass();

public:
	Project(unsigned int width, unsigned int height, const std::string& windowtitle):
		m_window(sf::VideoMode(width, height), windowtitle, sf::Style::Default, sf::ContextSettings(32))	{}
	void init();
	void run();
};

#endif // PROJECT_H