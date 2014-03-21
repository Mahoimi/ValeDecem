#include <Project.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Project::init(){
	// Vertical synchronization
	m_window.setVerticalSyncEnabled(true);

	// Initialize GLEW
	GLenum error;
    if ((error = glewInit()) != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(error));
    }

	// Set projection matrix
    m_projectionMatrix = glm::perspective(45.f, m_window.getSize().x / (float) m_window.getSize().y, 0.1f, 1000.f);

	// Load Shaders
    m_skyboxGLSL.m_program.load("../../shaders/skybox.vs.glsl", "../../shaders/skybox.fs.glsl");
    m_gbufferGLSL.m_program.load("../../shaders/gbuffer.vs.glsl", "../../shaders/gbuffer.fs.glsl");
    m_oodGLSL.m_program.load("../../shaders/ood.vs.glsl", "../../shaders/ood.fs.glsl");
    m_texturedMeshGLSL.m_program.load("../../shaders/gbuffer.vs.glsl", "../../shaders/texturedMesh.fs.glsl");
    m_blitGLSL.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/blit.fs.glsl");
    m_ambiantLightGLSL.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/ambiantLight.fs.glsl");
    m_pointLightGLSL.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/pointLight.fs.glsl");
    m_directionalLightGLSL.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/directionalLight.fs.glsl");
    m_spotLightGLSL.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/spotLight.fs.glsl");
    m_shadowGLSL.m_program.load("../../shaders/gbuffer.vs.glsl", "../../shaders/shadow.fs.glsl");
    m_blurGLSL.m_program.load("../../shaders/blit.vs.glsl","../../shaders/blur.fs.glsl");
    m_cocGLSL.m_program.load("../../shaders/blit.vs.glsl","../../shaders/coc.fs.glsl");
    m_dofGLSL.m_program.load("../../shaders/blit.vs.glsl","../../shaders/dof.fs.glsl");

	// Set uniform locations
    m_skyboxGLSL.m_modelLocation = m_skyboxGLSL.m_program.getUniformLocation("Model");
    m_skyboxGLSL.m_viewLocation = m_skyboxGLSL.m_program.getUniformLocation("View");
    m_skyboxGLSL.m_projectionLocation = m_skyboxGLSL.m_program.getUniformLocation("Projection");
    m_skyboxGLSL.m_skyboxTextureLocation = m_skyboxGLSL.m_program.getUniformLocation("SkyboxTexture");

	m_gbufferGLSL.m_modelLocation = m_gbufferGLSL.m_program.getUniformLocation("Model");
	m_gbufferGLSL.m_viewLocation = m_gbufferGLSL.m_program.getUniformLocation("View");
	m_gbufferGLSL.m_projectionLocation = m_gbufferGLSL.m_program.getUniformLocation("Projection");
	m_gbufferGLSL.m_diffuseLocation = m_gbufferGLSL.m_program.getUniformLocation("Diffuse");
	m_gbufferGLSL.m_specularLocation = m_gbufferGLSL.m_program.getUniformLocation("Specular");

    m_oodGLSL.m_modelLocation = m_oodGLSL.m_program.getUniformLocation("Model");
    m_oodGLSL.m_viewLocation = m_oodGLSL.m_program.getUniformLocation("View");
    m_oodGLSL.m_projectionLocation = m_oodGLSL.m_program.getUniformLocation("Projection");
    m_oodGLSL.m_colorLocation = m_oodGLSL.m_program.getUniformLocation("MeshColor");

    m_texturedMeshGLSL.m_modelLocation = m_texturedMeshGLSL.m_program.getUniformLocation("Model");
    m_texturedMeshGLSL.m_viewLocation = m_texturedMeshGLSL.m_program.getUniformLocation("View");
    m_texturedMeshGLSL.m_projectionLocation = m_texturedMeshGLSL.m_program.getUniformLocation("Projection");
    m_texturedMeshGLSL.m_diffuseLocation = m_texturedMeshGLSL.m_program.getUniformLocation("Diffuse");
    m_texturedMeshGLSL.m_specularLocation = m_texturedMeshGLSL.m_program.getUniformLocation("Specular");

    m_shadowGLSL.m_modelLocation = m_shadowGLSL.m_program.getUniformLocation("Model");
    m_shadowGLSL.m_viewLocation = m_shadowGLSL.m_program.getUniformLocation("View");
    m_shadowGLSL.m_projectionLocation = m_shadowGLSL.m_program.getUniformLocation("Projection");

	m_blitGLSL.m_modelLocation = m_blitGLSL.m_program.getUniformLocation("Model");
	m_blitGLSL.m_viewLocation = m_blitGLSL.m_program.getUniformLocation("View");
	m_blitGLSL.m_projectionLocation = m_blitGLSL.m_program.getUniformLocation("Projection");
	m_blitGLSL.m_textureLocation = m_blitGLSL.m_program.getUniformLocation("Texture");

    m_ambiantLightGLSL.m_lightColorLocation = m_ambiantLightGLSL.m_program.getUniformLocation("LightColor");
    m_ambiantLightGLSL.m_lightIntensityLocation = m_ambiantLightGLSL.m_program.getUniformLocation("LightIntensity");
    m_ambiantLightGLSL.m_materialLocation = m_ambiantLightGLSL.m_program.getUniformLocation("Material");

	m_pointLightGLSL.m_cameraPositionLocation = m_pointLightGLSL.m_program.getUniformLocation("CameraPosition");
	m_pointLightGLSL.m_inverseViewProjectionLocation = m_pointLightGLSL.m_program.getUniformLocation("InverseViewProjection");
	m_pointLightGLSL.m_lightPositionLocation = m_pointLightGLSL.m_program.getUniformLocation("LightPosition");
	m_pointLightGLSL.m_lightColorLocation = m_pointLightGLSL.m_program.getUniformLocation("LightColor");
	m_pointLightGLSL.m_lightIntensityLocation = m_pointLightGLSL.m_program.getUniformLocation("LightIntensity");
	m_pointLightGLSL.m_materialLocation = m_pointLightGLSL.m_program.getUniformLocation("Material");
	m_pointLightGLSL.m_normalLocation = m_pointLightGLSL.m_program.getUniformLocation("Normal");
	m_pointLightGLSL.m_depthLocation = m_pointLightGLSL.m_program.getUniformLocation("Depth");

	m_directionalLightGLSL.m_cameraPositionLocation = m_directionalLightGLSL.m_program.getUniformLocation("CameraPosition");
	m_directionalLightGLSL.m_inverseViewProjectionLocation = m_directionalLightGLSL.m_program.getUniformLocation("InverseViewProjection");
	m_directionalLightGLSL.m_lightDirectionLocation = m_directionalLightGLSL.m_program.getUniformLocation("LightDirection");
	m_directionalLightGLSL.m_lightColorLocation = m_directionalLightGLSL.m_program.getUniformLocation("LightColor");
	m_directionalLightGLSL.m_lightIntensityLocation = m_directionalLightGLSL.m_program.getUniformLocation("LightIntensity");
    m_directionalLightGLSL.m_lightProjectionLocation = m_directionalLightGLSL.m_program.getUniformLocation("LightProjection");
    m_directionalLightGLSL.m_shadowBiasLocation = m_directionalLightGLSL.m_program.getUniformLocation("ShadowBias");
    m_directionalLightGLSL.m_shadowSamplesLocation = m_directionalLightGLSL.m_program.getUniformLocation("ShadowSamples");
    m_directionalLightGLSL.m_shadowSampleSpreadLocation = m_directionalLightGLSL.m_program.getUniformLocation("ShadowSampleSpread");
	m_directionalLightGLSL.m_materialLocation = m_directionalLightGLSL.m_program.getUniformLocation("Material");
	m_directionalLightGLSL.m_normalLocation = m_directionalLightGLSL.m_program.getUniformLocation("Normal");
	m_directionalLightGLSL.m_depthLocation = m_directionalLightGLSL.m_program.getUniformLocation("Depth");
    m_directionalLightGLSL.m_shadowLocation = m_directionalLightGLSL.m_program.getUniformLocation("Shadow");

	m_spotLightGLSL.m_cameraPositionLocation = m_spotLightGLSL.m_program.getUniformLocation("CameraPosition");
	m_spotLightGLSL.m_inverseViewProjectionLocation = m_spotLightGLSL.m_program.getUniformLocation("InverseViewProjection");
    m_spotLightGLSL.m_lightPositionLocation = m_spotLightGLSL.m_program.getUniformLocation("LightPosition");
	m_spotLightGLSL.m_lightDirectionLocation = m_spotLightGLSL.m_program.getUniformLocation("LightDirection");
	m_spotLightGLSL.m_lightColorLocation = m_spotLightGLSL.m_program.getUniformLocation("LightColor");
	m_spotLightGLSL.m_lightIntensityLocation = m_spotLightGLSL.m_program.getUniformLocation("LightIntensity");
    m_spotLightGLSL.m_lightProjectionLocation = m_spotLightGLSL.m_program.getUniformLocation("LightProjection");
    m_spotLightGLSL.m_shadowBiasLocation = m_spotLightGLSL.m_program.getUniformLocation("ShadowBias");
	m_spotLightGLSL.m_materialLocation = m_spotLightGLSL.m_program.getUniformLocation("Material");
	m_spotLightGLSL.m_normalLocation = m_spotLightGLSL.m_program.getUniformLocation("Normal");
	m_spotLightGLSL.m_depthLocation = m_spotLightGLSL.m_program.getUniformLocation("Depth");
    m_spotLightGLSL.m_shadowLocation = m_spotLightGLSL.m_program.getUniformLocation("Shadow");

    m_blurGLSL.m_modelLocation = m_blurGLSL.m_program.getUniformLocation("Model");
    m_blurGLSL.m_viewLocation = m_blurGLSL.m_program.getUniformLocation("View");
    m_blurGLSL.m_projectionLocation = m_blurGLSL.m_program.getUniformLocation("Projection");
    m_blurGLSL.m_textureLocation = m_blurGLSL.m_program.getUniformLocation("Texture");
    m_blurGLSL.m_sampleCountLocation = m_blurGLSL.m_program.getUniformLocation("SampleCount");

    m_cocGLSL.m_modelLocation = m_cocGLSL.m_program.getUniformLocation("Model");
    m_cocGLSL.m_viewLocation = m_cocGLSL.m_program.getUniformLocation("View");
    m_cocGLSL.m_projectionLocation = m_cocGLSL.m_program.getUniformLocation("Projection");
    m_cocGLSL.m_screenToViewLocation = m_cocGLSL.m_program.getUniformLocation("ScreenToView");
    m_cocGLSL.m_depthLocation = m_cocGLSL.m_program.getUniformLocation("Depth");
    m_cocGLSL.m_focusLocation = m_cocGLSL.m_program.getUniformLocation("Focus");

    m_dofGLSL.m_modelLocation = m_dofGLSL.m_program.getUniformLocation("Model");
    m_dofGLSL.m_viewLocation = m_dofGLSL.m_program.getUniformLocation("View");
    m_dofGLSL.m_projectionLocation = m_dofGLSL.m_program.getUniformLocation("Projection");
    m_dofGLSL.m_colorLocation = m_dofGLSL.m_program.getUniformLocation("Color");
    m_dofGLSL.m_cocLocation = m_dofGLSL.m_program.getUniformLocation("CoC");
    m_dofGLSL.m_blurLocation = m_dofGLSL.m_program.getUniformLocation("Blur");

	// Load texture
    m_diffuseTexture.load("../../assets/textures/spnza_bricks_a_diff.tga");
    m_specularTexture.load("../../assets/textures/spnza_bricks_a_spec.tga");

    m_skyboxTexture.load("../../assets/textures/skybox/",
                         "spacebox_right.png",
                         "spacebox_left.png",
                         "spacebox_top.png",
                         "spacebox_bottom.png",
                         "spacebox_front.png",
                         "spacebox_back.png");


	// Set GBuffer for deferred rendering
	m_gbuffer.init(m_window.getSize().x, m_window.getSize().y);

    // Set ShadowMaps for shadow mapping
    //m_shadowMapSpotLight.init(1024,1024);
    m_shadowMapDirectionnalLight.init(2048,2048);

    // Set framebuffer for post effects with the depth texture of the gbuffer
    m_fxfbo.init(m_window.getSize().x, m_window.getSize().y);

	// Init VAO/VBO for 3D primitives / meshes
    m_cube.init();
	m_blitPlane.init(1.f);
    m_sponza.load("../../assets/sponza/sponza.obj");
    m_tardis.load("../../assets/tardis/tardis.obj");
    m_ood.load("../../assets/ood/ood.obj");

    // Init model matrices
    m_sponzaMatrix = glm::scale(m_modelMatrix, glm::vec3(0.01f));
    m_tardisPosition = glm::vec3(0,0,0);
    m_tardisRotationAxe = glm::vec3(0,1,0);
    m_tardisRotation = 0;

	// Init lights
    m_ambiantLight.init(glm::vec3(0.6f, 0.6f, 1), 0.18f);
    m_directionalLight.init(glm::vec3(0.25f, -1, 0), glm::vec3(0.4f, 0.4f, 1), .2f, 0.001f, 6, 1800);
    m_cameraPointLight.init(m_camera.getPosition(), glm::vec3(1, 1, 1), 4);

    m_tardisPointLight.init(glm::vec3(0, 3, -0.7f), glm::vec3(1, 1, 1), 2);
    m_tardisSpotLight.init(glm::vec3(-1, 5, 0), glm::vec3(1, -1, 1), glm::vec3(0.5f, 1, 1), 1);

    m_oodPointLight[0].init(glm::vec3(0), glm::vec3(1, 1, .8f), 1); // yellow-white
    m_oodPointLight[1].init(glm::vec3(0), glm::vec3(.6f, 1, .6f), 1); // green
    m_oodPointLight[2].init(glm::vec3(0), glm::vec3(.6f, .6f, 1), 1); // blue

    for (unsigned int i = 3; i < 9; ++i){ // golden-yellow variations
        float freq = 0.3f;
        m_oodPointLight[i].init(glm::vec3(0), glm::vec3(sin(freq*i)*0.5+1, sin(freq*i+1)*0.5+1, sin(freq*i+2)*0.5+1), 1);
    }

    // Fx parameters
    m_focus = glm::vec3(5.f, 1.f, 50.f);
    m_sampleCount = 10.f;

    // Init music
    assert(m_music.openFromFile("../../assets/music/ValeDecem.ogg"));
    m_music.play();

    // Animation parameters
    m_animationSequence = 1;
    m_newSequence = 1;
    m_initSequence = false;
    m_endSequence = false;

    // Init GUI
    m_gui.init(m_window.getSize().x, m_window.getSize().y, "Debug window");

    m_gui.addParameter(&m_fps, TW_TYPE_FLOAT, "fps_count", "label=FPS",false);

    m_gui.addParameter(&m_newSequence, TW_TYPE_CHAR, "new_sequence", "label='Selected sequence' min=1 max=15 step=1");
    m_gui.addPlayButton("play_sequence",this,"label='Play sequence'");

    m_gui.addParameter(&m_displaySponza, TW_TYPE_BOOL8, "display_sponza", "group='Display' label='Sponza'");
    m_gui.addParameter(&m_displayTardis, TW_TYPE_BOOL8, "display_tardis", "group='Display' label='Tardis'");
    m_gui.addParameter(&m_displayCameraPointLight, TW_TYPE_BOOL8, "display_camera_pl", "group='Display' label='Camera PointLight'");

    m_gui.addParameter(&m_camera.getPosition(), TW_TYPE_DIR3F, "camera_position", "group='Camera' label='Position'");
    m_gui.addParameter(&m_camera.getPhi(), TW_TYPE_FLOAT, "camera_phi", "group='Camera' label='Phi' step=1");
    m_gui.addParameter(&m_camera.getTheta(), TW_TYPE_FLOAT, "camera_theta", "group='Camera' label='Theta' step=1");
    m_gui.addParameter(&m_cameraPointLight.getPosition(), TW_TYPE_DIR3F, "camera_pl_position", "group='Camera' label='Position'");
    m_gui.addParameter(&m_cameraPointLight.getColor(), TW_TYPE_COLOR3F, "camera_pl_color", "group='Camera' label='Color'");
    m_gui.addParameter(&m_cameraPointLight.getIntensity(), TW_TYPE_FLOAT, "camera_pl_intensity", "group='Camera' label='Intensity' min=0 max=10 step=0.01");

    m_gui.addParameter(&m_tardisPosition, TW_TYPE_DIR3F, "tardis_position", "group='Tardis' label='Position'");
    m_gui.addParameter(&m_tardisRotationAxe, TW_TYPE_DIR3F, "tardis_rot_axe", "group='Tardis' label='Rotation Axe'");
    m_gui.addParameter(&m_tardisRotation, TW_TYPE_FLOAT, "tardis_rotation", "group='Tardis' label='Rotation angle'");

    m_gui.addParameter(&m_oodPointLight[0].getPosition(), TW_TYPE_DIR3F, "ood_position0", "group='Oods' label='Position0'");
    m_gui.addParameter(&m_oodPointLight[1].getPosition(), TW_TYPE_DIR3F, "ood_position1", "group='Oods' label='Position1'");
    m_gui.addParameter(&m_oodPointLight[2].getPosition(), TW_TYPE_DIR3F, "ood_position2", "group='Oods' label='Position2'");
    m_gui.addParameter(&m_oodPointLight[3].getPosition(), TW_TYPE_DIR3F, "ood_position3", "group='Oods' label='Position3'");
    m_gui.addParameter(&m_oodPointLight[4].getPosition(), TW_TYPE_DIR3F, "ood_position4", "group='Oods' label='Position4'");
    m_gui.addParameter(&m_oodPointLight[5].getPosition(), TW_TYPE_DIR3F, "ood_position5", "group='Oods' label='Position5'");
    m_gui.addParameter(&m_oodPointLight[6].getPosition(), TW_TYPE_DIR3F, "ood_position6", "group='Oods' label='Position6'");
    m_gui.addParameter(&m_oodPointLight[7].getPosition(), TW_TYPE_DIR3F, "ood_position7", "group='Oods' label='Position7'");

    m_gui.addParameter(&m_ambiantLight.getColor(), TW_TYPE_COLOR3F, "ambiant_color", "group='AmbiantLight' label='Color'");
    m_gui.addParameter(&m_ambiantLight.getIntensity(), TW_TYPE_FLOAT, "ambiant_intensity", "group='AmbiantLight' label='Intensity' min=0 max=5 step=0.01");

    m_gui.addParameter(&m_directionalLight.getDirection(), TW_TYPE_DIR3F, "directional_direction", "group='DirectionalLight' label='Direction'");
    m_gui.addParameter(&m_directionalLight.getColor(), TW_TYPE_COLOR3F, "directional_color", "group='DirectionalLight' label='Color'");
    m_gui.addParameter(&m_directionalLight.getIntensity(), TW_TYPE_FLOAT, "directional_intensity", "group='DirectionalLight' label='Intensity' min=0 max=5 step=0.01");
    m_gui.addParameter(&m_directionalLight.getShadowBias(), TW_TYPE_FLOAT, "directional_shadowBias", "group='DirectionalLight' label='ShadowBias' min=0 max=5 step=0.001");
    m_gui.addParameter(&m_directionalLight.getShadowSamples(), TW_TYPE_FLOAT, "directional_shadowSamples", "group='DirectionalLight' label='ShadowSamples' min=0 max=16 step=1");
    m_gui.addParameter(&m_directionalLight.getShadowSampleSpread(), TW_TYPE_FLOAT, "directional_shadowSampleSpread", "group='DirectionalLight' label='ShadowSampleSpread' min=0 max=10000 step=50");

    m_gui.addParameter(&m_tardisPointLight.getPosition(), TW_TYPE_DIR3F, "tardis_pl_position", "group='TardisPointLight' label='Position'");
    m_gui.addParameter(&m_tardisPointLight.getColor(), TW_TYPE_COLOR3F, "tardis_pl_color", "group='TardisPointLight' label='Color'");
    m_gui.addParameter(&m_tardisPointLight.getIntensity(), TW_TYPE_FLOAT, "tardis_pl_intensity", "group='TardisPointLight' label='Intensity' min=0 max=5 step=0.01");

    m_gui.addParameter(&m_focus.x, TW_TYPE_FLOAT, "focus_plane", "group='DepthOfField' label='Focus plane' min=0 max=100 step=0.1");
    m_gui.addParameter(&m_focus.y, TW_TYPE_FLOAT, "focus_near", "group='DepthOfField' label='Focus near' min=0 max=100 step=0.1");
    m_gui.addParameter(&m_focus.z, TW_TYPE_FLOAT, "focus_far", "group='DepthOfField' label='Focus far' min=0 max=100 step=0.1");
    m_gui.addParameter(&m_sampleCount, TW_TYPE_FLOAT, "sample_count", "group='DepthOfField' label='Sample count' min=1 max=50");
}

void Project::getInput(){
	// Define the speed of the camera
    float speed = .25f;

	// Mouse commands
	m_mousePosition = sf::Mouse::getPosition(m_window);

	// Move the camera according to the mouse position when the left clic is pressed
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        m_camera.rotatePhi(-0.4f*(m_mousePosition.x - m_prevMousePosition.x));
        m_camera.rotateTheta(-0.4f*(m_mousePosition.y - m_prevMousePosition.y));
    }

	// Replace the previous position by the actual position
	m_prevMousePosition = m_mousePosition;

	// Keyboard commands
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        m_camera.moveFront(speed);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		m_camera.moveLeft(speed);
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        m_camera.moveFront(-speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        m_camera.moveLeft(-speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)){
        m_camera.moveUp(speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){
        m_camera.moveUp(-speed);
    }
}

// Clear all information remaining in the buffers we use
void Project::clearBuffers(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_gbuffer.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shadowMapDirectionnalLight.bindFramebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    m_shadowMapSpotLight.bindFramebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    for (unsigned int i = 0; i < 4; ++i){
        m_fxfbo.bindFramebufferWith(i);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Project::gBufferPass(){
    // Enable Depth test
    glEnable(GL_DEPTH_TEST);

    // Set Viewport
    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

	// Use gbuffer shaders
	m_gbufferGLSL.m_program.use();

	// Bind fbo
	m_gbuffer.bindFramebuffer();

    // Use mesh shader
    m_texturedMeshGLSL.m_program.use();

    // RENDER SPONZA ////////////////////////////////////////////////////////////////////////////////////////////
    if(m_displaySponza){
        // Send uniform data
        glUniform1i(m_texturedMeshGLSL.m_diffuseLocation, 0);
        glUniform1i(m_texturedMeshGLSL.m_specularLocation, 10);
        glUniformMatrix4fv(m_texturedMeshGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_sponzaMatrix));
        glUniformMatrix4fv(m_texturedMeshGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_texturedMeshGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        // Draw
        m_sponza.render();
    }

    // RENDER TARDIS ////////////////////////////////////////////////////////////////////////////////////////////
    if(m_displayTardis){
        // Reset model matrix
        m_modelMatrix = glm::mat4(1.f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_tardisPosition);
        m_modelMatrix = glm::rotate(m_modelMatrix, m_tardisRotation, m_tardisRotationAxe);
        m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.1f));

        // Send uniform data
        glUniform1i(m_texturedMeshGLSL.m_diffuseLocation, 0);
        glUniform1i(m_texturedMeshGLSL.m_specularLocation, 10);
        glUniformMatrix4fv(m_texturedMeshGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_texturedMeshGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_texturedMeshGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        // Draw
        m_tardis.render();
    }

    // Unbind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Disable Depth test
    glDisable(GL_DEPTH_TEST);
}

void Project::shadowMappingPass(){
    // Enable Depth test
    glEnable(GL_DEPTH_TEST);

    // Use gbuffer shaders
    m_shadowGLSL.m_program.use();

    // Bind fbo
    m_shadowMapDirectionnalLight.bindFramebuffer();

    // Set Viewport
    glViewport(0, 0, 2048, 2048);

    // Send uniform data
    glUniformMatrix4fv(m_shadowGLSL.m_projectionLocation, 1, 0, glm::value_ptr(m_directionalLight.getLightToShadowMap()));
    glUniformMatrix4fv(m_shadowGLSL.m_viewLocation, 1, 0, glm::value_ptr(m_directionalLight.getWorldToLight()));

    // RENDER SPONZA ////////////////////////////////////////////////////////////////////////////////////////////

    if(m_displaySponza){
        glUniformMatrix4fv(m_shadowGLSL.m_modelLocation, 1, 0, glm::value_ptr(m_sponzaMatrix));

        // Draw
        m_sponza.render();
    }

    // RENDER TARDIS ////////////////////////////////////////////////////////////////////////////////////////////
    if(m_displayTardis){
        // Reset model matrix
        m_modelMatrix = glm::mat4(1.f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_tardisPosition);
        m_modelMatrix = glm::rotate(m_modelMatrix, m_tardisRotation, m_tardisRotationAxe);
        m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.1f));


        // Send uniform data
        glUniformMatrix4fv(m_shadowGLSL.m_modelLocation, 1, 0, glm::value_ptr(m_modelMatrix));

        // Draw
        m_tardis.render();
    }

    // RENDER OOD ////////////////////////////////////////////////////////////////////////////////////////////////

    for(unsigned int i=0; i<OODS_NUMBER; ++i){
        if(m_displayOods[i]){
            // Reset model matrix
            m_modelMatrix = glm::mat4(1.f);
            m_modelMatrix = glm::translate(m_modelMatrix,m_oodPointLight[i].getPosition());
            m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.25f));

            // Send uniform data
            glUniformMatrix4fv(m_shadowGLSL.m_modelLocation, 1, 0, glm::value_ptr(m_modelMatrix));

            // Draw
            m_ood.render();
        }
    }

    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Disable Depth test
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);
}

void Project::lightingByAmbiantLight(){
    // Use pointLight shaders
    m_ambiantLightGLSL.m_program.use();

    // Send uniform value
    glUniform1i(m_ambiantLightGLSL.m_materialLocation, 0);

    glUniform3fv(m_ambiantLightGLSL.m_lightColorLocation, 1, glm::value_ptr(m_ambiantLight.getColor()));
    glUniform1f(m_ambiantLightGLSL.m_lightIntensityLocation, m_ambiantLight.getIntensity());

    // Bind textures : material
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));

    m_blitPlane.render();
}


void Project::lightingByPointLight(){
	// Use pointLight shaders
	m_pointLightGLSL.m_program.use();

	// Send uniform value
	glUniform1i(m_pointLightGLSL.m_materialLocation, 0);
	glUniform1i(m_pointLightGLSL.m_normalLocation, 1);
	glUniform1i(m_pointLightGLSL.m_depthLocation, 2);

    // Bind textures : material, normal and depth
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

	glm::mat4 inverseViewProjection = glm::transpose(glm::inverse(m_projectionMatrix * m_viewMatrix));

	glUniform3fv(m_pointLightGLSL.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
	glUniformMatrix4fv(m_pointLightGLSL.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

    // RENDER TARDIS POINTLIGHT ///////////////////////////////////////////////////////////////////////////////
    if(m_displayTardis){

        // Calculate new position of tardisPointLight
        m_modelMatrix = glm::mat4(1.f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_tardisPosition);
        m_modelMatrix = glm::rotate(m_modelMatrix, m_tardisRotation, m_tardisRotationAxe);
        m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0,3,0));
        glm::vec4 m_newPosition = m_modelMatrix * glm::vec4(0,0,0,1);
        m_tardisPointLight.setPosition(glm::vec3(m_newPosition.x, m_newPosition.y, m_newPosition.z));

        glUniform3fv(m_pointLightGLSL.m_lightPositionLocation, 1, glm::value_ptr(m_tardisPointLight.getPosition()));
        glUniform3fv(m_pointLightGLSL.m_lightColorLocation, 1, glm::value_ptr(m_tardisPointLight.getColor()));
        glUniform1f(m_pointLightGLSL.m_lightIntensityLocation, m_tardisPointLight.getIntensity());

        m_blitPlane.render();
    }

    // RENDER CAMERA POINTLIGHT
    if (m_displayCameraPointLight){
        glUniform3fv(m_pointLightGLSL.m_lightPositionLocation, 1, glm::value_ptr(m_cameraPointLight.getPosition()));
        glUniform3fv(m_pointLightGLSL.m_lightColorLocation, 1, glm::value_ptr(m_cameraPointLight.getColor()));
        glUniform1f(m_pointLightGLSL.m_lightIntensityLocation, m_cameraPointLight.getIntensity());

        m_blitPlane.render();
    }

    // RENDER OODS POINTLIGHT //////////////////////////////////////////////////////////////////////////////////
    for(unsigned int i = 0; i<OODS_NUMBER; ++i){
        if(m_displayOods[i]){
            glUniform3fv(m_pointLightGLSL.m_lightPositionLocation, 1, glm::value_ptr(m_oodPointLight[i].getPosition()));
            glUniform3fv(m_pointLightGLSL.m_lightColorLocation, 1, glm::value_ptr(m_oodPointLight[i].getColor()));
            glUniform1f(m_pointLightGLSL.m_lightIntensityLocation, m_oodPointLight[i].getIntensity());

            m_blitPlane.render();
        }
    }
}

void Project::lightingByDirectionalLight(){
	// Use directionalLight shaders
	m_directionalLightGLSL.m_program.use();

	// Send uniform value
	glUniform1i(m_directionalLightGLSL.m_materialLocation, 0);
	glUniform1i(m_directionalLightGLSL.m_normalLocation, 1);
	glUniform1i(m_directionalLightGLSL.m_depthLocation, 2);
    glUniform1i(m_directionalLightGLSL.m_shadowLocation, 3);

	glm::mat4 inverseViewProjection = glm::transpose(glm::inverse(m_projectionMatrix * m_viewMatrix));

	glUniform3fv(m_directionalLightGLSL.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
	glUniformMatrix4fv(m_directionalLightGLSL.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

	glUniform3fv(m_directionalLightGLSL.m_lightDirectionLocation, 1, glm::value_ptr(m_directionalLight.getDirection()));
	glUniform3fv(m_directionalLightGLSL.m_lightColorLocation, 1, glm::value_ptr(m_directionalLight.getColor()));
	glUniform1f(m_directionalLightGLSL.m_lightIntensityLocation, m_directionalLight.getIntensity());
    glUniformMatrix4fv(m_directionalLightGLSL.m_lightProjectionLocation, 1, 0, glm::value_ptr(m_directionalLight.getWorldToShadowMap()));
    glUniform1f(m_directionalLightGLSL.m_shadowBiasLocation, m_directionalLight.getShadowBias());
    glUniform1f(m_directionalLightGLSL.m_shadowSamplesLocation, m_directionalLight.getShadowSamples());
    glUniform1f(m_directionalLightGLSL.m_shadowSampleSpreadLocation, m_directionalLight.getShadowSampleSpread());

    // Bind textures : material, normal, depth and shadow
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapDirectionnalLight.getTexture());

	m_blitPlane.render();
}

void Project::lightingBySpotLight(){
    /*
    // Use spotLight shaders
	m_spotLightGLSL.m_program.use();


	// Send uniform value
	glUniform1i(m_spotLightGLSL.m_materialLocation, 0);
	glUniform1i(m_spotLightGLSL.m_normalLocation, 1);
	glUniform1i(m_spotLightGLSL.m_depthLocation, 2);
    glUniform1i(m_spotLightGLSL.m_shadowLocation, 3);

	glm::mat4 inverseViewProjection = glm::transpose(glm::inverse(m_projectionMatrix * m_viewMatrix));

	glUniform3fv(m_spotLightGLSL.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
	glUniformMatrix4fv(m_spotLightGLSL.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

	glUniform3fv(m_spotLightGLSL.m_lightDirectionLocation, 1, glm::value_ptr(m_spotLight.getDirection()));
	glUniform3fv(m_spotLightGLSL.m_lightPositionLocation, 1, glm::value_ptr(m_spotLight.getPosition()));
	glUniform3fv(m_spotLightGLSL.m_lightColorLocation, 1, glm::value_ptr(m_spotLight.getColor()));
	glUniform1f(m_spotLightGLSL.m_lightIntensityLocation, m_spotLight.getIntensity());
    glUniformMatrix4fv(m_spotLightGLSL.m_lightProjectionLocation, 1, 0, glm::value_ptr(m_spotLight.getWorldToShadowMap()));
    glUniform1f(m_spotLightGLSL.m_shadowBiasLocation, 0.001f);


    // Bind textures : material, normal, depth and shadow
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapSpotLight.getTexture());

    m_blitPlane.render();
    */
}

void Project::lightingPass(){
    m_fxfbo.bindFramebufferWith(0);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    lightingByAmbiantLight();
    lightingByDirectionalLight();


    lightingByPointLight();
   // lightingBySpotLight();

    glDisable(GL_BLEND);

    // Unbind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Project::unlightPass(){
    m_fxfbo.bindFramebufferWith(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_gbuffer.getTexture(2), 0);

    glEnable(GL_DEPTH_TEST);
    // Enable CULL FACE
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    // Use gbuffer shaders
    m_skyboxGLSL.m_program.use();

    // Reset model matrix
    m_modelMatrix = glm::mat4(1.f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_camera.getPosition());
    m_modelMatrix = glm::scale(m_modelMatrix,glm::vec3(20.f));

    // Send uniform data
    glUniform1i(m_skyboxGLSL.m_skyboxTextureLocation, 0);
    glUniformMatrix4fv(m_skyboxGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    glUniformMatrix4fv(m_skyboxGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    glUniformMatrix4fv(m_skyboxGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

    // Bind textures
    m_skyboxTexture.bind(GL_TEXTURE0);

    // Draw
    m_cube.render();

    // RENDER OOD ////////////////////////////////////////////////////////////////////////////////////////////
    for(unsigned int i=0; i<OODS_NUMBER; ++i){
        if(m_displayOods[i]){
            m_fxfbo.bindFramebufferWith(3);

            m_oodGLSL.m_program.use();

            // Reset model matrix
            m_modelMatrix = glm::mat4(1.f);
            m_modelMatrix = glm::translate(m_modelMatrix, m_oodPointLight[i].getPosition());
            m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.25f));

            // Send uniform data
            glUniform3fv(m_oodGLSL.m_colorLocation, 1, glm::value_ptr(m_oodPointLight[i].getColor()));
            glUniformMatrix4fv(m_oodGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
            glUniformMatrix4fv(m_oodGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
            glUniformMatrix4fv(m_oodGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

            // Draw
            m_ood.render();
        }
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    // Unbind fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Project::fxPass(){
    if (m_displayDof){
        // COC ////////////////////////
        m_fxfbo.bindFramebufferWith(1);

        glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

        m_screenToView = glm::inverse(m_projectionMatrix);

        // Use coc shaders
        m_cocGLSL.m_program.use();

        glUniform1i(m_cocGLSL.m_depthLocation, 0);
        glUniform3fv(m_cocGLSL.m_focusLocation,1, glm::value_ptr(m_focus));
        glUniformMatrix4fv(m_cocGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_cocGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_cocGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
        glUniformMatrix4fv(m_cocGLSL.m_screenToViewLocation, 1, GL_FALSE, glm::value_ptr(m_screenToView));

        // Bind depth texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

        m_blitPlane.render();

        // BLUR //////////////////////
        // Bind framebuffer
        m_fxfbo.bindFramebufferWith(2);

        glViewport(0, 0, m_window.getSize().x / 2, m_window.getSize().y / 2);

        // Use blur shaders
        m_blurGLSL.m_program.use();

        glUniform1i(m_blurGLSL.m_textureLocation, 0);
        glUniform1f(m_blurGLSL.m_sampleCountLocation, m_sampleCount);
        glUniformMatrix4fv(m_blurGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_blurGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_blurGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        // Bind depth texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(0));

        m_blitPlane.render();

        // DEPTH OF FIELD //////////////
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

        m_dofGLSL.m_program.use();
        glUniform1i(m_dofGLSL.m_colorLocation, 0);
        glUniform1i(m_dofGLSL.m_blurLocation, 1);
        glUniform1i(m_dofGLSL.m_cocLocation, 2);
        glUniformMatrix4fv(m_dofGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_dofGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_dofGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        // Bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(0));
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(2));
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(1));

        m_blitPlane.render();
    }
    else {
        // Display lightedscene texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

        m_blitGLSL.m_program.use();
        glUniform1i(m_blitGLSL.m_textureLocation, 0);
        glUniformMatrix4fv(m_blitGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_blitGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_blitGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        // Bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(0));

        m_blitPlane.render();
    }
    if (m_displayOods){
        // BLUR GLOWMAP
        m_fxfbo.bindFramebufferWith(2);

        m_blurGLSL.m_program.use();
        glUniform1i(m_blurGLSL.m_textureLocation, 0);
        glUniform1f(m_blurGLSL.m_sampleCountLocation, m_sampleCount);
        glUniformMatrix4fv(m_blurGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_blurGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_blurGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

        // Bind depth texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(3));

        m_blitPlane.render();

        // BLEND GLOWMAP
        glEnable(GL_BLEND);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Use blit shaders
        m_blitGLSL.m_program.use();

        // Send uniform value
        glUniform1i(m_blitGLSL.m_textureLocation, 0);

        // Bind color texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(2));

        m_blitPlane.render();

        glDisable(GL_BLEND);
    }
    // Debind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Project::blitPass(){
    // Use default buffers
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Use blit shaders
	m_blitGLSL.m_program.use();

	// Send uniform value
	glUniform1i(m_blitGLSL.m_textureLocation, 0);

    // DIFFUSE TEXTURE ///////////////////////////////////////////////////
	// Set Viewport 
    glViewport(0, 0, m_window.getSize().x/8, m_window.getSize().y/8);

	// Bind color texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));

	// Render plane
	m_blitPlane.render();

    // NORMAL TEXTURE ///////////////////////////////////////////////////
	// Viewport 
    glViewport(m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

	// Bind normal texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));

	// Render plane
	m_blitPlane.render();

    // DEPTH TEXTURE ///////////////////////////////////////////////////
    // Viewport
    glViewport(2*m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

	// Bind depth texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

	// Render plane
    m_blitPlane.render();

    // SHADOWMAP TEXTURE ///////////////////////////////////////////////////
    // Viewport
    glViewport(3*m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

    // Bind shadowMap texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapDirectionnalLight.getTexture());

    // Render plane
    m_blitPlane.render();

    // LIGHTEDSCENE TEXTURE ///////////////////////////////////////////////////
    // Viewport
    glViewport(4*m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

    // Bind normal texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(0));

    // Render plane
    m_blitPlane.render();

    // COC TEXTURE ///////////////////////////////////////////////////
    // Viewport
    glViewport(5*m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

    // Bind depth texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(1));

    // Render plane
    m_blitPlane.render();

    // BLUR TEXTURE ///////////////////////////////////////////////////
    // Viewport
    glViewport(6*m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

    // Bind shadowMap texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(2));

    // Render plane
    m_blitPlane.render();

    // GLOWMAP TEXTURE ///////////////////////////////////////////////////
    // Viewport
    glViewport(7*m_window.getSize().x/8, 0, m_window.getSize().x/8, m_window.getSize().y/8);

    // Bind shadowMap texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(3));

    // Render plane
    m_blitPlane.render();
}

// Play the selected sequence
void Project::playNewSequence(){
    m_animationSequence = m_newSequence;
    m_initSequence = false;
}

// Set all display booleans to true/false
void Project::setAllDisplay(bool b){
    for (unsigned int i = 0; i < OODS_NUMBER; ++i)
        m_displayOods[i] = b;
    m_displayTardis = b;
    m_displaySponza = b;
    m_displayCameraPointLight = b;
    m_displayDof = b;
}

// Empty space view
// Camera Phi goes from 230 to -77 with a slight acceleration and deceleration
void Project::emptySpaceSequence(const float elapsedTime){
    if (!m_initSequence){
        // Music
        m_music.stop();
        m_music.play();

        // Display
        setAllDisplay(false);

        // Camera
        m_camera.setPosition(glm::vec3(0, 16, 0));
        m_camera.setPhi(230);
        m_camera.setTheta(54);

        // Speed
        m_speed = 1.f;

        m_initSequence = true;
    }

    if (m_camera.getPhi() > -30){
        // Accelerate
        if (m_speed < 20.f){
            m_speed += 0.05f;
        }
    }
    else{
        // Decelerate
        if (m_speed > 1.f){
            m_speed -= 0.05f;
        }
    }
    if(m_camera.getPhi() > -77){
        m_camera.rotatePhi(-m_speed*elapsedTime);
    }
    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

// Travelling in the center of the attrium
// Camera PosX goes from -13 to 0 with a slight acceleration and deceleration
void Project::emptySponzaTravellingSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displaySponza = true;
        m_displayDof = true;
        m_displayCameraPointLight = true;

        // Camera
        m_camera.setPosition(glm::vec3(-13, 3.f, -0.35f));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(90);
        m_camera.setTheta(0);

        // Fx
        m_focus = glm::vec3(2,1,20);

        // Speed
        m_speed = 0.5f;
        m_speed2 = 0.3f;

        m_initSequence = true;
    }

    m_cameraPointLight.setPosition(m_camera.getPosition());

    if (m_camera.getPosition().y < 2){
        if (m_speed2 > 0.1f){
            m_speed2 -= 0.01f;
        }
    }

    if (m_camera.getPosition().y > 1.25){
        m_camera.getPosition().y -= m_speed2 * elapsedTime;
    }

    if (m_camera.getPosition().x < -2){
        // Accelerate
        if (m_speed < 2){
            m_speed += 0.01f;
        }
    }
    else{
        // Decelerate
        if (m_speed > 1.f){
            m_speed -= 0.01f;
        }
    }

    if(m_camera.getPosition().x < 0){
        m_camera.getPosition().x += m_speed * elapsedTime;
    }
    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

// Pan from bottom to top in the center of the attrium
// Camera Phi 240 -> 120
// Camera Theta 0 -> 70 -> 0
void Project::emptySponzaPanSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displaySponza = true;
        m_displayDof = true;
        m_displayCameraPointLight = true;

        // Camera
        m_camera.setPosition(glm::vec3(0, 1.25f, -.5f));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(2.f);
        m_camera.setPhi(240);
        m_camera.setTheta(0);

        // Fx
        m_focus = glm::vec3(2,1,20);

        // Speed
        m_speed = 1.f;
        m_speed2 = 1.f;

        m_initSequence = true;
    }

    m_cameraPointLight.setPosition(m_camera.getPosition());

    // Acceleration of Phi
    if (m_camera.getPhi() > 130){

        if (m_speed2 < 12.f){
            m_speed2 += 0.1f;
        }
    }

    m_camera.getPhi() -= m_speed2 * elapsedTime;

    if (m_camera.getPhi() > 180){
        // Acceleration of Theta
        if (m_camera.getTheta() < 60){

            if (m_speed < 20.f){
                m_speed += 0.2f;
            }
        }
        else{
            if (m_speed > 0.2f){
                m_speed -= 0.2f;
            }
        }

        if (m_camera.getTheta() < 70) m_camera.getTheta() += m_speed * elapsedTime;
    }
    else{
        // Acceleration of Theta
        if (m_camera.getTheta() > 30){

            if (m_speed < 20.f){
                m_speed += 0.2f;
            }
        }
        else{
            if (m_speed > 0.2f){
                m_speed -= 0.2f;
            }
        }
        if (m_camera.getTheta() > 0) m_camera.getTheta() -= m_speed * elapsedTime;
    }


    if(m_camera.getPhi() < 120){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

// A ood appears at the center of the atrium
void Project::oodApparitionSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displaySponza = true;
        m_displayDof = true;
        m_displayOods[0] = true;

        // Oods
        m_oodPointLight[0].setPosition(glm::vec3(0, -0.3f, 0));
        m_oodPointLight[0].setIntensity(1);

        // Camera
        m_camera.setPosition(glm::vec3(-3, 0.1f, 1.4f));
        m_camera.setPhi(110);
        m_camera.setTheta(5);

        // Fx
        m_focus = glm::vec3(2,1,20);

        // Speed
        m_speed = 0.15f;

        m_initSequence = true;
    }

    m_cameraPointLight.setPosition(m_camera.getPosition());

    if(m_oodPointLight[0].getPosition().y < 0.75){
        m_oodPointLight[0].getPosition().y += m_speed * elapsedTime;
    }
    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

// Two oods pop out the fountains
void Project::oodFountainSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displaySponza = true;
        m_displayDof = true;
        m_displayOods[1] = true;
        m_displayOods[2] = true;

        // Oods
        m_oodPointLight[1].setPosition(glm::vec3(11.2f, 1.f, 3.90f));
        m_oodPointLight[1].setIntensity(1);
        m_oodPointLight[2].setPosition(glm::vec3(11.4f, 0.2f, -4.8f));
        m_oodPointLight[2].setIntensity(1);

        // Camera
        m_camera.setPosition(glm::vec3(12.5, 2.2f, -6.3));
        m_camera.setPhi(-22);
        m_camera.setTheta(-11);

        // Fx
        m_focus = glm::vec3(2,1,20);

        // Speed
        m_speed = 0.25f;

        m_initSequence = true;
    }

    if(m_oodPointLight[1].getPosition().y < 3){
        m_oodPointLight[1].getPosition().y += m_speed * elapsedTime;
        m_oodPointLight[2].getPosition().y += m_speed * elapsedTime;
    }
    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

// Oods circle at the center of Sponza
void Project::oodCircleElevationSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displaySponza = true;
        m_displayDof = true;
        m_displayOods[0] = true;

        // Oods
        m_oodPointLight[0].setPosition(glm::vec3(0, 2, 0));
        m_oodPointLight[0].setIntensity(1);

        glm::mat4 centerMatrix = glm::translate(glm::mat4(1), glm::vec3(0, -3, 0));

        for (unsigned int i = 3; i < 9; ++i){
            m_displayOods[i] = true;

            glm::mat4 rotMatrix = glm::rotate(centerMatrix, i*60.f, glm::vec3(0,1,0));
            glm::mat4 radiusMatrix = glm::translate(rotMatrix, glm::vec3(0,0,1));

            glm::vec4 oodPosition = radiusMatrix * glm::vec4(0,0,0,1);

            m_oodPointLight[i].setPosition(glm::vec3(oodPosition.x, oodPosition.y+i*0.5f, oodPosition.z));
            m_oodPointLight[i].setIntensity(1);
        }

        // Camera
        m_camera.setPosition(glm::vec3(6.4, 0.2f, 1.3));
        m_camera.setPhi(-100);
        m_camera.setTheta(0);

        // Fx
        m_focus = glm::vec3(2,1,20);

        // Speed
        m_speed = 0.2f;

        m_initSequence = true;
    }

    if(m_oodPointLight[0].getPosition().y < 4){
        m_oodPointLight[0].getPosition().y += m_speed * elapsedTime;
        for (unsigned int i = 3; i < 9; ++i) {
            if (m_oodPointLight[0].getPosition().y > m_oodPointLight[i].getPosition().y)
                 m_oodPointLight[i].getPosition().y += (1.f/i + m_speed)* elapsedTime;
            else
                m_oodPointLight[i].getPosition().y += m_speed * elapsedTime;
        }
    }
    if(m_camera.getTheta() < 20){
        m_camera.rotateTheta(10*m_speed*elapsedTime);
    }
    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}


// Oods dispersion
void Project::oodCircleDispersionSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displaySponza = true;
        m_displayDof = true;
        m_displayOods[0] = true;

        // Oods
        m_oodPointLight[0].setPosition(glm::vec3(0, 4, 0));
        m_oodPointLight[0].setIntensity(1);
        m_dispersionRadius = glm::vec3(0,0,1);

        for (unsigned int i = 3; i < 9; ++i){
            m_displayOods[i] = true;
            m_oodPointLight[i].setIntensity(1);
        }

        // Camera
        m_camera.setPosition(glm::vec3(10.5f, 6.7f, 0.8f));
        m_camera.setPhi(-100);
        m_camera.setTheta(-20);

        // Fx
        m_focus = glm::vec3(8,1,20);

        // Speed
        m_speed = 0.8f;
        m_initSequence = true;
    }


    if(m_oodPointLight[0].getPosition().y < 8){
        m_oodPointLight[0].getPosition().y += m_speed * elapsedTime;
        glm::mat4 centerMatrix = glm::translate(glm::mat4(1), glm::vec3(0, m_oodPointLight[0].getPosition().y, 0));
        m_dispersionRadius.z += m_speed * elapsedTime;
        for (unsigned int i = 3; i < 9; ++i){
            glm::mat4 rotMatrix = glm::rotate(centerMatrix, i*60.f, glm::vec3(0,1,0));
            glm::mat4 radiusMatrix = glm::translate(rotMatrix, m_dispersionRadius);

            glm::vec4 oodPosition = radiusMatrix * glm::vec4(0,0,0,1);

            m_oodPointLight[i].setPosition(glm::vec3(oodPosition.x, oodPosition.y, oodPosition.z));
        }
    }
    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::tardisSpaceSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displayTardis = true;
        m_displayCameraPointLight = true;

        // Tardis
        m_tardisPosition = glm::vec3(0.f, 18.5, 0.5f);
        m_tardisRotationAxe = glm::vec3(-3, 9, 0);
        m_tardisRotation = 0;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(-22, 20, 5));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5);
        m_camera.setPhi(-220);
        m_camera.setTheta(0);

        // Fx
        m_focus = glm::vec3(8,1,20);

        // Speed
        m_speed = 4;
        m_speed2 = 8;

        m_initSequence = true;
    }


    m_tardisPointLight.getIntensity() += m_speed2 * elapsedTime;
    if (m_tardisPointLight.getIntensity() > 8) m_speed2 = -8;
    if (m_tardisPointLight.getIntensity() < 0.1f) m_speed2 = 8;

    if(m_camera.getPosition().x < 0.5){
        m_camera.getPosition().x += m_speed * elapsedTime;
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_tardisRotation += 12.5f * m_speed * elapsedTime;
    }

    else{
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::travellingOnTheRoofSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displayCameraPointLight = true;
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;
        m_displayOods[0] = true;

        // Ood
        m_oodPointLight[0].setPosition(glm::vec3(0, 8, 0));
        m_oodPointLight[0].setIntensity(1);

        // Tardis
        m_tardisPosition = glm::vec3(20,17,0);
        m_tardisRotationAxe = glm::vec3(-3, 9, 0);
        m_tardisRotation = 0.f;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(17.5f,20.5f,4));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(2.f);
        m_camera.setPhi(-108);
        m_camera.setTheta(-36);

        // Fx
        m_focus = glm::vec3(3,1,20);

        // Animation speed
        m_speed = 2.f;
        m_speed2 = 8;
        m_initSequence = true;
    }

    m_tardisPointLight.getIntensity() += m_speed2 * elapsedTime;
    if (m_tardisPointLight.getIntensity() > 8) m_speed2 = -8;
    if (m_tardisPointLight.getIntensity() < 0.1f) m_speed2 = 8;

    m_oodPointLight[0].getPosition().y += m_speed*0.2f*elapsedTime;

    m_camera.moveFront(m_speed * elapsedTime);
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_tardisPosition.x -= 2.f*m_speed*elapsedTime;
    m_tardisPosition.y -= 0.5f*m_speed*elapsedTime;
    m_tardisRotation += 100*elapsedTime;

    if (m_tardisPosition.x <= 0){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::tardisLandingWingSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;
        m_displayOods[1] = true;
        m_displayOods[2] = true;

        // Ood
        m_oodPointLight[1].setPosition(glm::vec3(-4, 6, 3.5));
        m_oodPointLight[1].setIntensity(1);
        m_oodPointLight[2].setPosition(glm::vec3(4, 6, -5));
        m_oodPointLight[2].setIntensity(1);

        // Tardis
        m_tardisPosition = glm::vec3(0,10,0);
        m_tardisRotationAxe = glm::vec3(0, 1, 0);
        m_tardisRotation = 0.f;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(0,8,5));
        m_camera.setPhi(-180);
        m_camera.setTheta(0);

        // Fx
        m_focus = glm::vec3(3,1,20);

        // Animation speed
        m_speed = 0.5f;
        m_speed2 = 8;
        m_initSequence = true;
    }

    m_tardisPointLight.getIntensity() += m_speed2 * elapsedTime;
    if (m_tardisPointLight.getIntensity() > 8) m_speed2 = -8;
    if (m_tardisPointLight.getIntensity() < 0.1f) m_speed2 = 8;

    m_camera.getPosition().y -= 0.5f*m_speed * elapsedTime;
    m_tardisPosition.y -= m_speed * elapsedTime;
    m_tardisRotation += 30*m_speed * elapsedTime;
    m_oodPointLight[1].getPosition().x += m_speed * elapsedTime;
    m_oodPointLight[2].getPosition().x -= m_speed * elapsedTime;

    if (m_tardisPosition.y < 3){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::tardisLandingAttriumSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;

        // Tardis
        m_tardisPosition = glm::vec3(0,5,0);
        m_tardisRotationAxe = glm::vec3(0, 1, 0);
        m_tardisRotation = 90.f;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(-5,0.5f,0));
        m_camera.setPhi(-270);
        m_camera.setTheta(45);

        // Fx
        m_focus = glm::vec3(3,1,20);

        // Animation speed
        m_speed = 0.5f;
        m_speed2 = 8;
        m_initSequence = true;
    }

    m_tardisPointLight.getIntensity() += m_speed2 * elapsedTime;
    if (m_tardisPointLight.getIntensity() > 8) m_speed2 = -8;
    if (m_tardisPointLight.getIntensity() < 0.1f) m_speed2 = 8;

    m_tardisPosition.y -= m_speed * elapsedTime;
    m_tardisRotation += 30*m_speed * elapsedTime;
    m_camera.getTheta() -= 7*m_speed * elapsedTime;

    if (m_tardisPosition.y < 0){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::oodsToTheTardisSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        for (unsigned int i = 0; i < OODS_NUMBER; ++i)
            m_displayOods[i] = true;
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;

        // Oods
        glm::mat4 centerMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0.5, 0));
        m_dispersionRadius = glm::vec3(10,10,10);
        for (unsigned int i = 0; i < OODS_NUMBER; ++i){
            glm::mat4 rotMatrix = glm::rotate(centerMatrix, i*360.f/OODS_NUMBER*m_dispersionRadius.z, glm::vec3(0,1,0));
            glm::mat4 radiusMatrix = glm::translate(rotMatrix, m_dispersionRadius);

            glm::vec4 oodPosition = radiusMatrix * glm::vec4(0,0,0,1);

            m_oodPointLight[i].setPosition(glm::vec3(oodPosition.x, oodPosition.y, oodPosition.z));
            m_oodPointLight[i].setIntensity(1);
        }

        // Tardis
        m_tardisPosition = glm::vec3(0,0,0);
        m_tardisRotationAxe = glm::vec3(0, 1, 0);
        m_tardisRotation = 246;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(-10,10,0));
        m_camera.setPhi(-270);
        m_camera.setTheta(-40);

        // Fx
        m_focus = glm::vec3(7,1,20);

        // Animation speed
        m_speed = 0.3f;
        m_initSequence = true;
    }

    m_camera.moveFront(0.5f*m_speed*elapsedTime);
    m_dispersionRadius -= glm::vec3(m_speed * elapsedTime);
    glm::mat4 centerMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0.5, 0));
    for (unsigned int i = 0; i < OODS_NUMBER; ++i){
        glm::mat4 rotMatrix = glm::rotate(centerMatrix, i*360.f/OODS_NUMBER*m_dispersionRadius.z, glm::vec3(0,1,0));
        glm::mat4 radiusMatrix = glm::translate(rotMatrix, m_dispersionRadius);
        glm::vec4 oodPosition = radiusMatrix * glm::vec4(0,0,0,1);

        m_oodPointLight[i].setPosition(glm::vec3(oodPosition.x, oodPosition.y, oodPosition.z));
    }

    if (m_dispersionRadius.x<0.1f){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::suspensSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        for (unsigned int i = 0; i < OODS_NUMBER; ++i)
            m_displayOods[i] = true;
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;

        // Oods
        for (unsigned int i = 0; i < OODS_NUMBER; ++i){
            m_oodPointLight[i].setPosition(glm::vec3(0, 1, 0));
            m_oodPointLight[i].setIntensity(1);
        }

        // Tardis
        m_tardisPosition = glm::vec3(0,0,0);
        m_tardisRotationAxe = glm::vec3(0, 1, 0);
        m_tardisRotation = 246;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(-3,0.5f,-1.3f));
        m_camera.setPhi(-280);
        m_camera.setTheta(15);

        // Fx
        m_focus = glm::vec3(1,1,20);

        // Animation speed
        m_speed = 0.3f;
        m_initSequence = true;
    }

    m_focus.x += m_speed * elapsedTime;
    m_camera.getPosition().x -= m_speed * elapsedTime;

    for (unsigned int i = 0; i < OODS_NUMBER; ++i){
        if (m_oodPointLight[i].getIntensity() > 0.01f)
            m_oodPointLight[i].getIntensity() -= 2*m_speed * elapsedTime;
    }

    if (m_camera.getPosition().x < -4.8){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::explosionSequence(const float elapsedTime){
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;

        // Oods
        for (unsigned int i = 0; i < OODS_NUMBER; ++i){
            m_displayOods[i] = true;
            m_oodPointLight[i].setPosition(glm::vec3(0, 1, 0));
            m_oodPointLight[i].setIntensity(1);
        }

        // Tardis
        m_tardisPosition = glm::vec3(0,0,0);
        m_tardisRotationAxe = glm::vec3(0, 1, 0);
        m_tardisRotation = 246;
        m_tardisPointLight.setIntensity(0.f);

        // Camera
        m_camera.setPosition(glm::vec3(-3,1,0));
        m_camera.setPhi(-270);
        m_camera.setTheta(10);

        // Fx
        m_focus = glm::vec3(1,1,20);

        // Animation speed
        m_speed = 1;
        m_initSequence = true;
    }

    if (m_speed < 20){
        m_speed += 10.f*m_speed*elapsedTime;
    }
    m_camera.getPosition().x -= m_speed * elapsedTime;
    m_tardisRotation += 10*m_speed * elapsedTime;
    if (m_tardisPointLight.getIntensity() < 11){
        m_tardisPointLight.getIntensity() += m_speed * elapsedTime;
        for (unsigned int i = 0; i < OODS_NUMBER; ++i){
            m_oodPointLight[i].getIntensity() += m_speed * elapsedTime;
        }
    }

    if (m_camera.getPosition().x < -13){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::endExplosionSequence(const float elapsedTime){
    bool lightTurnedOff = false;
    if (!m_initSequence){
        // Display
        setAllDisplay(false);
        m_displayTardis = true;
        m_displaySponza = true;
        m_displayDof = true;

        // Tardis
        m_tardisPosition = glm::vec3(0,0,0);
        m_tardisRotationAxe = glm::vec3(0, 1, 0);
        m_tardisRotation = 246;
        m_tardisPointLight.setIntensity(11);

        // Oods
        for (unsigned int i = 0; i < OODS_NUMBER; ++i){
            m_displayOods[i] = true;
            m_oodPointLight[i].setPosition(glm::vec3(0, 1, 0));
            m_oodPointLight[i].setIntensity(11);
        }

        // Camera
        m_camera.setPosition(glm::vec3(-6,9.9f,0));
        m_camera.setPhi(-270);
        m_camera.setTheta(-53);

        // Fx
        m_focus = glm::vec3(5,1,20);

        // Animation speed
        m_speed = 200;
        m_speed2 = 8;
        m_speed3 = 3;
        m_initSequence = true;
    }

    if (m_oodPointLight[0].getIntensity() > 0.1f){
        for (unsigned int i = 0; i < OODS_NUMBER; ++i){
            m_oodPointLight[i].getIntensity() -= m_speed3 * elapsedTime;
        }
    }
    else lightTurnedOff = true;

    if (!lightTurnedOff){
        m_speed += 5.7f;
    }
    else{
        m_speed -= 4;
    }

    m_tardisRotation += m_speed * elapsedTime;

    m_tardisPointLight.getIntensity() += m_speed2 * elapsedTime;
    if (m_tardisPointLight.getIntensity() > 8) m_speed2 = -8;
    if (m_tardisPointLight.getIntensity() < 2) m_speed2 = 8;

    if (m_speed < 0){
        // Finish sequence
        m_initSequence = false;
        m_endSequence = true;
    }
}

void Project::animation(const float elapsedTime){
    switch(m_animationSequence){
        case 1:
            emptySpaceSequence(elapsedTime);
            break;
        case 2:
            emptySponzaTravellingSequence(elapsedTime);
            break;
        case 3:
            emptySponzaPanSequence(elapsedTime);
            break;
        case 4:
            oodApparitionSequence(elapsedTime);
            break;
        case 5:
            oodFountainSequence(elapsedTime);
            break;
        case 6:
            oodCircleElevationSequence(elapsedTime);
            break;
        case 7:
            oodCircleDispersionSequence(elapsedTime);
            break;
        case 8:
            tardisSpaceSequence(elapsedTime);
            break;
        case 9:
            travellingOnTheRoofSequence(elapsedTime);
            break;
        case 10:
            tardisLandingWingSequence(elapsedTime);
            break;
        case 11:
            tardisLandingAttriumSequence(elapsedTime);
            break;
        case 12:
            oodsToTheTardisSequence(elapsedTime);
            break;
        case 13:
            suspensSequence(elapsedTime);
            break;
        case 14:
            explosionSequence(elapsedTime);
            break;
        case 15:
            endExplosionSequence(elapsedTime);
            break;
    }

    // If the sequence is over, we move to the next one
    if (m_endSequence) {
        m_animationSequence++;
        m_endSequence = false;
    }
}


void Project::run(){
    sf::Clock clock;
    float elapsedTime = 0.f;

	m_prevMousePosition = sf::Mouse::getPosition(m_window);

    // Run the main loop
    bool running = true;
    while (running)
    {
        elapsedTime = clock.restart().asSeconds();
        m_fps = 1.f/ elapsedTime;

        // Handle events
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            int handled = TwEventSFML(&event, 2,1);
            if(!handled)
            {
                if (event.type == sf::Event::Closed)
                {
                    // end the program
                    running = false;
                }
                else if (event.type == sf::Event::Resized)
                {
                    // adjust the viewport when the window is resized
                    glViewport(0, 0, event.size.width, event.size.height);
                }
                else if (event.type == sf::Event::KeyPressed){
                    // Switch to debug mode
                    if (event.key.code == sf::Keyboard::D){
                        m_debugMode = !m_debugMode;
                    }
                }
            }
        }

		// Keyboard / mouse inputs
		getInput();

        // Update camera position/rotation and model matrices
        animation(elapsedTime);

        m_camera.computeDirectionVectors();
        m_viewMatrix = m_camera.getViewMatrix();

        // Clear the buffers
        clearBuffers();
		
		// Render the geometry in the gbuffer
        gBufferPass();

        // Create the lights shadow maps
        shadowMappingPass();

		// Use the textures in the gbuffer to calculate the illumination
        lightingPass();

        // Render the skybox
        unlightPass();

        // Post-effects techniques (DoF)
        fxPass();

        // Debugging mode = Blit windows + GUI
        if (m_debugMode){
            // Debugging windows to see what's inside the gbuffer
            blitPass();

            // GUI
            m_gui.draw();
        }

        // end the current frame (internally swaps the front and back buffers)
        m_window.display();
    }
}
