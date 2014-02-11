#include <Project.h>

#include <glm/glm.hpp>
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
	m_stack.set(glm::perspective(45.f, m_window.getSize().x / (float) m_window.getSize().y, 0.1f, 100.f));

	// Load Shaders
	m_program.load("./shaders/simple.vs.glsl", "./shaders/simple.fs.glsl");
	m_program.use();

	// Set uniform location
	m_MVPLocation = m_program.getUniformLocation("MVP");
	m_DiffuseLocation = m_program.getUniformLocation("Diffuse");

	// Load texture
	m_diffuseTexture.load("./assets/textures/spnza_bricks_a_diff.tga");

	// Set GBuffer for deferred rendering
	m_gbuffer.init(m_window.getSize().x, m_window.getSize().y);

	// Init VAO/VBO for 3D primitives / meshes
	m_cube.init();
	m_plane.init();
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

void Project::firstPass(){
	// Enable Depth test
	glEnable(GL_DEPTH_TEST);

	// Set viewport to all the window
	glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

	// Save current matrix of the stack
	m_stack.push();

		// Multiply Projection and View matrices
		m_stack.mult(m_camera.getViewMatrix());
		
		// Send uniform data
		glUniform1i(m_DiffuseLocation, 0);
		glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, glm::value_ptr(m_stack.top()));

		// Bind texture
		m_diffuseTexture.bind(GL_TEXTURE0);

		// Draw
		m_cube.render();

		// Save current matrix of the stack
		m_stack.push();

			// Linear transformations
			m_stack.scale(glm::vec3(50));
			m_stack.rotate(90, glm::vec3(1, 0, 0));
			m_stack.translate(glm::vec3(0, 0, 1.f/50));
		
			// Send uniform data
			glUniform1i(m_DiffuseLocation, 0);
			glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, glm::value_ptr(m_stack.top()));

			// Bind texture
			m_diffuseTexture.bind(GL_TEXTURE0);

			// Draw
			m_plane.render();

		// Reset stack
		m_stack.pop();

	// Reset stack
	m_stack.pop();
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
		
		// Clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Render the geometry in the gbuffer
		firstPass();

		// Use the textures in the gbuffer to calculate the illumination

		// Debugging windows to see what's inside the gbuffer

        // end the current frame (internally swaps the front and back buffers)
        m_window.display();
    }
}