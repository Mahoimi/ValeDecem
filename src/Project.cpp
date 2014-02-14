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
	m_projectionMatrix = glm::perspective(45.f, m_window.getSize().x / (float) m_window.getSize().y, 0.1f, 100.f);

	// Load Shaders
	m_gbufferGLSL.m_program.load("./shaders/gbuffer.vs.glsl", "./shaders/gbuffer.fs.glsl");
	m_blitGLSL.m_program.load("./shaders/blit.vs.glsl", "./shaders/blit.fs.glsl");
	m_shadingGLSL.m_program.load("./shaders/blit.vs.glsl", "./shaders/light.fs.glsl");

	// Set uniform locations
	m_gbufferGLSL.m_modelLocation = m_gbufferGLSL.m_program.getUniformLocation("Model");
	m_gbufferGLSL.m_viewLocation = m_gbufferGLSL.m_program.getUniformLocation("View");
	m_gbufferGLSL.m_projectionLocation = m_gbufferGLSL.m_program.getUniformLocation("Projection");
	m_gbufferGLSL.m_diffuseLocation = m_gbufferGLSL.m_program.getUniformLocation("Diffuse");
	m_gbufferGLSL.m_specularLocation = m_gbufferGLSL.m_program.getUniformLocation("Specular");

	m_blitGLSL.m_modelLocation = m_blitGLSL.m_program.getUniformLocation("Model");
	m_blitGLSL.m_viewLocation = m_blitGLSL.m_program.getUniformLocation("View");
	m_blitGLSL.m_projectionLocation = m_blitGLSL.m_program.getUniformLocation("Projection");
	m_blitGLSL.m_textureLocation = m_blitGLSL.m_program.getUniformLocation("Texture");

	m_shadingGLSL.m_cameraPositionLocation = m_shadingGLSL.m_program.getUniformLocation("CameraPosition");
	m_shadingGLSL.m_inverseViewProjectionLocation = m_shadingGLSL.m_program.getUniformLocation("InverseViewProjection");
	m_shadingGLSL.m_lightPositionLocation = m_shadingGLSL.m_program.getUniformLocation("LightPosition");
	m_shadingGLSL.m_lightColorLocation = m_shadingGLSL.m_program.getUniformLocation("LightColor");
	m_shadingGLSL.m_lightIntensityLocation = m_shadingGLSL.m_program.getUniformLocation("LightIntensity");
	m_shadingGLSL.m_materialLocation = m_shadingGLSL.m_program.getUniformLocation("Material");
	m_shadingGLSL.m_normalLocation = m_shadingGLSL.m_program.getUniformLocation("Normal");
	m_shadingGLSL.m_depthLocation = m_shadingGLSL.m_program.getUniformLocation("Depth");

	// Load texture
	m_diffuseTexture.load("./assets/textures/spnza_bricks_a_diff.tga");
	m_specularTexture.load("./assets/textures/spnza_bricks_a_spec.tga");

	// Set GBuffer for deferred rendering
	m_gbuffer.init(m_window.getSize().x, m_window.getSize().y);

	// Init VAO/VBO for 3D primitives / meshes
	m_cube.init();
	m_floorPlane.init(50.f);
	m_blitPlane.init(1.f);
}

void Project::getInput(){
	// Define the speed of the camera
    float speed = .25f;

	// Mouse commands
	m_mousePosition = sf::Mouse::getPosition(m_window);

	// Move the camera according to the mouse position when the left clic is pressed
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_camera.rotateLeft(-0.4f*(m_mousePosition.x - m_prevMousePosition.x));
        m_camera.rotateUp(-0.4f*(m_mousePosition.y - m_prevMousePosition.y));
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
}

void Project::gBufferPass(){
	// Enable Depth test
	glEnable(GL_DEPTH_TEST);

	// Use gbuffer shaders
	m_gbufferGLSL.m_program.use();

	// Bind fbo
	m_gbuffer.bindFramebuffer();

	// Clear the current buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset model matrix
	m_modelMatrix = glm::mat4(1.f);
	m_viewMatrix = m_camera.getViewMatrix();

	// Set viewport to all the window
	glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

	// Send uniform data
	glUniform1i(m_gbufferGLSL.m_diffuseLocation, 0);
	glUniform1i(m_gbufferGLSL.m_specularLocation, 1);
	glUniformMatrix4fv(m_gbufferGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
	glUniformMatrix4fv(m_gbufferGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
	glUniformMatrix4fv(m_gbufferGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

	// Bind textures
	m_diffuseTexture.bind(GL_TEXTURE0);
	m_specularTexture.bind(GL_TEXTURE1);

	// Draw
	m_cube.render();

	// Reset model matrix
	m_modelMatrix = glm::mat4(1.f);

	// Linear transformations
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(50));
	m_modelMatrix = glm::rotate(m_modelMatrix, -90.f, glm::vec3(1, 0, 0));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0, 0, -0.5f/50.f));
		
	// Send uniform data
	glUniform1i(m_gbufferGLSL.m_diffuseLocation, 0);
	glUniform1i(m_gbufferGLSL.m_specularLocation, 1);
	glUniformMatrix4fv(m_gbufferGLSL.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
	glUniformMatrix4fv(m_gbufferGLSL.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
	glUniformMatrix4fv(m_gbufferGLSL.m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

	// Bind textures
	m_diffuseTexture.bind(GL_TEXTURE0);
	m_specularTexture.bind(GL_TEXTURE1);

	// Draw
	m_floorPlane.render();

	// Unbind fbo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Disable Depth test
	glDisable(GL_DEPTH_TEST);
}

void Project::shadingPass(){
	// Clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shading shaders
	m_shadingGLSL.m_program.use();

	// Set Viewport 
    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

	// Light setting
	glm::vec3 lightPosition(1, 1, 1);
	glm::vec3 lightColor(1,1,1);
	float lightIntensity = 2.f;

	// Send uniform value
	glUniform1i(m_shadingGLSL.m_materialLocation, 0);
	glUniform1i(m_shadingGLSL.m_normalLocation, 1);
	glUniform1i(m_shadingGLSL.m_depthLocation, 2);

	glm::mat4 inverseViewProjection = glm::transpose(glm::inverse(m_projectionMatrix * m_viewMatrix));

	glUniform3fv(m_shadingGLSL.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
	glUniformMatrix4fv(m_shadingGLSL.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

	glUniform3fv(m_shadingGLSL.m_lightPositionLocation, 1, glm::value_ptr(lightPosition));
	glUniform3fv(m_shadingGLSL.m_lightColorLocation, 1, glm::value_ptr(lightColor));
	glUniform1f(m_shadingGLSL.m_lightIntensityLocation, lightIntensity);

	// Bind textures : material, normal and depth
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

	m_blitPlane.render();

}

void Project::blitPass(){
	// Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

	// Use blit shaders
	m_blitGLSL.m_program.use();

	// Send uniform value
	glUniform1i(m_blitGLSL.m_textureLocation, 0);

	// Set Viewport 
    glViewport(0, 0, m_window.getSize().x/3, m_window.getSize().y/4);

	// Bind color texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));

	// Render plane
	m_blitPlane.render();

	// Viewport 
    glViewport(m_window.getSize().x/3, 0, m_window.getSize().x/3, m_window.getSize().y/4);

	// Bind normal texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));

	// Render plane
	m_blitPlane.render();

	// Viewport
	glViewport(2*m_window.getSize().x/3, 0, m_window.getSize().x/3, m_window.getSize().y/4);

	// Bind depth texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

	// Render plane
	m_blitPlane.render();

	glDisable(GL_BLEND);
}

void Project::run(){
	m_prevMousePosition = sf::Mouse::getPosition(m_window);

    // Run the main loop
    bool running = true;
    while (running)
    {
        // Handle events
        sf::Event event;
        while (m_window.pollEvent(event))
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
        }

		// Keyboard / mouse inputs
		getInput();
		
		// Render the geometry in the gbuffer
		gBufferPass();

		// Use the textures in the gbuffer to calculate the illumination
		shadingPass();

		// Debugging windows to see what's inside the gbuffer
		blitPass();

		// GUI

        // end the current frame (internally swaps the front and back buffers)
        m_window.display();
    }
}