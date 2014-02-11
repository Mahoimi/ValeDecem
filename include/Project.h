#ifndef PROJECT_H
#define PROJECT_H

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Cube.h>
#include <Plane.h>
#include <GLProgram.h>
#include <MatrixStack.h>
#include <FreeFlyCamera.h>
#include <GLTexture.h>
#include <GBuffer.h>

class Project {
private:
	sf::Window m_window;

	Cube m_cube;
	Plane m_plane;
	GLProgram m_program;
	GLTexture m_diffuseTexture;
	MatrixStack m_stack;
	FreeFlyCamera m_camera;
	GBuffer m_gbuffer;

	GLuint m_MVPLocation;
	GLuint m_DiffuseLocation;

	sf::Vector2i m_mousePosition;
	sf::Vector2i m_prevMousePosition;

	void getInput();
	void firstPass();
	void secondPass();

public:
	Project(unsigned int width, unsigned int height, const std::string& windowtitle):
		m_window(sf::VideoMode(width, height), windowtitle, sf::Style::Default, sf::ContextSettings(32))	{}
	void init();
	void run();
};

#endif // PROJECT_H