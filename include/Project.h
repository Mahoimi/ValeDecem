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
	Plane m_plane;
	GLTexture m_diffuseTexture;
	GLTexture m_specularTexture;
	FreeFlyCamera m_camera;
	GBuffer m_gbuffer;

	struct GBufferPass {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_projectionLocation;
		GLuint m_diffuseLocation;
		GLuint m_specularLocation;
		GLProgram m_program;

		GBufferPass(){}
	};
	GBufferPass m_gbufferPass;

	struct BlitPass {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_projectionLocation;
		GLuint m_textureLocation;
		GLProgram m_program;

		BlitPass(){}
	};
	BlitPass m_blitPass;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	sf::Vector2i m_mousePosition;
	sf::Vector2i m_prevMousePosition;

	void getInput();
	void firstPass();
	void secondPass();
	void blitPass();

public:
	Project(unsigned int width, unsigned int height, const std::string& windowtitle):
		m_window(sf::VideoMode(width, height), windowtitle, sf::Style::Default, sf::ContextSettings(32))	{}
	void init();
	void run();
};

#endif // PROJECT_H