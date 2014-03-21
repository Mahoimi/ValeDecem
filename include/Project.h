#ifndef PROJECT_H
#define PROJECT_H

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio/Music.hpp>

#include <Cube.h>
#include <Plane.h>
#include <AmbiantLight.h>
#include <PointLight.h>
#include <DirectionalLight.h>
#include <SpotLight.h>
#include <GLProgram.h>
#include <FreeFlyCamera.h>
#include <CubemapTexture.h>
#include <GLTexture.h>
#include <GBuffer.h>
#include <ShadowMap.h>
#include <Mesh.h>
#include <FXFbo.h>
#include <GUI.h>

#define OODS_NUMBER 9

/*!
* \class Project
* Create and Handle the sfml window events
* Generate the OpenGL objects
* Make the passes to render the 3D scene
*/
class Project {
private:
	sf::Window m_window;

    // 3D Model
    Cube m_cube;
	Plane m_blitPlane;
    MeshRenderer m_sponza;
    MeshRenderer m_tardis;
    MeshRenderer m_ood;
    FreeFlyCamera m_camera;

    // Lights
    AmbiantLight m_ambiantLight;
    DirectionalLight m_directionalLight;
    PointLight m_cameraPointLight;
    PointLight m_tardisPointLight;
    SpotLight m_tardisSpotLight;
    PointLight m_oodPointLight[OODS_NUMBER];

    // Textures
    CubemapTexture m_skyboxTexture;
	GLTexture m_diffuseTexture;
	GLTexture m_specularTexture;
    GLTexture m_creditsTexture;

    // FBO
    GBuffer m_gbuffer;
    ShadowMap m_shadowMapSpotLight;
    ShadowMap m_shadowMapDirectionnalLight;
    FXFbo m_fxfbo;

    // Shaders
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
    GBufferGLSL m_texturedMeshGLSL;

    struct OodGLSL {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_colorLocation;
        GLProgram m_program;

        OodGLSL(){}
    };
    OodGLSL m_oodGLSL;

	struct BlitGLSL {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_projectionLocation;
		GLuint m_textureLocation;
		GLProgram m_program;

		BlitGLSL(){}
	};
	BlitGLSL m_blitGLSL;

    struct AmbiantLightGLSL {
        GLuint m_lightColorLocation;
        GLuint m_lightIntensityLocation;
        GLuint m_materialLocation;
        GLProgram m_program;

        AmbiantLightGLSL(){}
    };
    AmbiantLightGLSL m_ambiantLightGLSL;

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
        GLuint m_shadowBiasLocation;
        GLuint m_lightProjectionLocation;
        GLuint m_shadowSamplesLocation;
        GLuint m_shadowSampleSpreadLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
        GLuint m_shadowLocation;
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
        GLuint m_shadowBiasLocation;
        GLuint m_lightProjectionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
        GLuint m_shadowLocation;
		GLProgram m_program;

		SpotLightGLSL(){}
	};
	SpotLightGLSL m_spotLightGLSL;

    struct ShadowGLSL {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLProgram m_program;

        ShadowGLSL(){}
    };
    ShadowGLSL m_shadowGLSL;

    struct BlurGLSL {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_textureLocation;
        GLuint m_sampleCountLocation;
        GLProgram m_program;

        BlurGLSL(){}
    };
    BlurGLSL m_blurGLSL;

    struct CocGLSL {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_depthLocation;
        GLuint m_screenToViewLocation;
        GLuint m_focusLocation;
        GLProgram m_program;

        CocGLSL(){}
    };
    CocGLSL m_cocGLSL;

    struct DofGLSL {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_projectionLocation;
        GLuint m_colorLocation;
        GLuint m_blurLocation;
        GLuint m_cocLocation;
        GLProgram m_program;

        DofGLSL(){}
    };
    DofGLSL m_dofGLSL;

    // Model, View and Projection matrices
    glm::vec3 m_tardisPosition;
    glm::vec3 m_tardisRotationAxe;
    float m_tardisRotation;
    glm::vec3 m_dispersionRadius;
    float m_speed;
    float m_speed2;
    float m_speed3;

    glm::mat4 m_sponzaMatrix;

    glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

    // DOF parameters
    glm::mat4 m_screenToView;
    glm::vec3 m_focus;
    float m_sampleCount;

    // GUI
    GUI m_gui;
	sf::Vector2i m_mousePosition;
	sf::Vector2i m_prevMousePosition;
    float m_fps;
    bool m_debugMode;

    // Sound
    sf::Music m_music;

    // Animation parameters
    unsigned char m_animationSequence;
    unsigned char m_newSequence;
    bool m_initSequence;
    bool m_endSequence;
    bool m_displayTardis;
    bool m_displayOods[OODS_NUMBER];
    bool m_displaySponza;
    bool m_displayCameraPointLight;
    bool m_displaySpotlight;
    bool m_displayDof;
    bool m_displayCredits;

    void getInput();
    void clearBuffers();
    void gBufferPass();
    void directionalLightShadowMapping();
    void spotlightShadowMapping();
    void lightingByAmbiantLight();
	void lightingByPointLight();
	void lightingByDirectionalLight();
	void lightingBySpotLight();
	void lightingPass();
    void unlightPass();
    void fxPass();
	void blitPass();

    void animation(const float elapsedTime);
    void setAllDisplay(bool b);

    void emptySpaceSequence(const float elapsedTime);
    void emptySponzaTravellingSequence(const float elapsedTime);
    void emptySponzaPanSequence(const float elapsedTime);
    void oodApparitionSequence(const float elapsedTime);
    void oodFountainSequence(const float elapsedTime);
    void oodCircleElevationSequence(const float elapsedTime);
    void oodCircleDispersionSequence(const float elapsedTime);
    void tardisSpaceSequence(const float elapsedTime);
    void travellingOnTheRoofSequence(const float elapsedTime);
    void tardisLandingWingSequence(const float elapsedTime);
    void tardisLandingAttriumSequence(const float elapsedTime);
    void oodsToTheTardisSequence(const float elapsedTime);
    void suspensSequence(const float elapsedTime);
    void explosionSequence(const float elapsedTime);
    void endExplosionSequence(const float elapsedTime);
    void screwdiverSpotlightSequence(const float elapsedTime);
    void creditsSequence();

public:
	Project(unsigned int width, unsigned int height, const std::string& windowtitle):
        m_window(sf::VideoMode(width, height), windowtitle, sf::Style::Default, sf::ContextSettings(32)),
        m_debugMode(false){}
	void init();
	void run();
    void playNewSequence();
};

#endif // PROJECT_H
