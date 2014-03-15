#ifndef PROJECT_H
#define PROJECT_H

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Cube.h>
#include <Plane.h>
#include <PointLight.h>
#include <DirectionalLight.h>
#include <SpotLight.h>
#include <GLProgram.h>
#include <FreeFlyCamera.h>
#include <CubemapTexture.h>
#include <GLTexture.h>
#include <GBuffer.h>
#include <Mesh.h>
#include <FXFbo.h>

/*!
* \class Project
* Create and Handle the sfml window events
* Generate the OpenGL objects
* Make the passes to render the 3D scene
*/
class Project {
private:
	sf::Window m_window;

    Cube m_cube;
	Plane m_floorPlane;
	Plane m_blitPlane;
    MeshRenderer m_sponza;
    MeshRenderer m_tardis;

	PointLight m_pointLight;
	DirectionalLight m_directionalLight;
	SpotLight m_spotLight;

    CubemapTexture m_skyboxTexture;

	GLTexture m_diffuseTexture;
	GLTexture m_specularTexture;
	FreeFlyCamera m_camera;
	GBuffer m_gbuffer;
    FXFbo m_fxfbo;

    struct SkyboxGLSL {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_skyboxTextureLocation;
        GLProgram m_program;

        SkyboxGLSL(){}
    };
    SkyboxGLSL m_skyboxGLSL;

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
    GBufferGLSL m_meshGLSL;

	struct BlitGLSL {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_projectionLocation;
		GLuint m_textureLocation;
		GLProgram m_program;

		BlitGLSL(){}
	};
	BlitGLSL m_blitGLSL;

	struct PointLightGLSL {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightPositionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
		GLProgram m_program;

		PointLightGLSL(){}
	};
	PointLightGLSL m_pointLightGLSL;

	struct DirectionalLightGLSL {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightDirectionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
		GLProgram m_program;

		DirectionalLightGLSL(){}
	};
	DirectionalLightGLSL m_directionalLightGLSL;

	struct SpotLightGLSL {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightPositionLocation;
		GLuint m_lightDirectionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
		GLProgram m_program;

		SpotLightGLSL(){}
	};
	SpotLightGLSL m_spotLightGLSL;


	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	sf::Vector2i m_mousePosition;
	sf::Vector2i m_prevMousePosition;

    bool m_debugMode;

	void getInput();
    void skyboxPass();
	void gBufferPass();
	void lightingByPointLight();
	void lightingByDirectionalLight();
	void lightingBySpotLight();
	void lightingPass();
    void fxPass();
	void blitPass();

public:
	Project(unsigned int width, unsigned int height, const std::string& windowtitle):
        m_window(sf::VideoMode(width, height), windowtitle, sf::Style::Default, sf::ContextSettings(32)),
        m_debugMode(false){}
	void init();
	void run();
};

#endif // PROJECT_H
