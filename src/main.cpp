#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Cube.h>
#include <Plane.h>
#include <GLProgram.h>
#include <MatrixStack.h>
#include <FreeFlyCamera.h>
#include <GLTexture.h>

int main()
{
    // Create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

	// Initialize GLEW
	GLenum error;
    if ((error = glewInit()) != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(error));
    }

    // Load resources, initialize the OpenGL states, ...
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	FreeFlyCamera camera;
	
	MatrixStack stack;
	stack.set(glm::perspective(45.f, window.getSize().x / (float) window.getSize().y, 0.1f, 100.f));

	GLProgram program;
	program.load("./shaders/simple.vs.glsl", "./shaders/simple.fs.glsl");
	program.use();

	GLuint MVPLocation = program.getUniformLocation("MVP");
	GLuint DiffuseLocation = program.getUniformLocation("Diffuse");

	GLTexture diffuseTexture;
	diffuseTexture.load("./assets/textures/spnza_bricks_a_diff.tga");

	Cube cube;
	Plane plane;

	cube.init();
	plane.init();

	sf::Vector2i prevMousePosition(sf::Mouse::getPosition(window));
	sf::Vector2i mousePosition;

    // Define the speed of the camera
    float speed = .25f;

	glEnable(GL_DEPTH_TEST);

    // Run the main loop
    bool running = true;
    while (running)
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
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

		// Mouse commands
		mousePosition = sf::Mouse::getPosition(window);

        // Move the camera according to the mouse position when the left clic is pressed
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            camera.rotateLeft(-0.4f*(mousePosition.x - prevMousePosition.x));
            camera.rotateUp(-0.4f*(mousePosition.y - prevMousePosition.y));
        }

        // Replace the previous position by the actual position
        prevMousePosition=mousePosition;

		// Keyboard commands
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            camera.moveFront(speed);
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			camera.moveLeft(speed);
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            camera.moveFront(-speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            camera.moveLeft(-speed);
        }

        // Clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Save current matrix of the stack
		stack.push();
		
		// Multiply Projection and View matrices
		stack.mult(camera.getViewMatrix());

		// Send uniform data
		glUniform1i(DiffuseLocation, 0);
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(stack.top()));

		// Bind texture
		diffuseTexture.bind(GL_TEXTURE0);

		// Draw
		cube.render();

		// Unbind texture
		glActiveTexture(0);

		// Reset stack
		stack.pop();

		 // Save current matrix of the stack
		stack.push();

		// Multiply Projection and View matrices
		stack.mult(camera.getViewMatrix());

		// Multiply ViewProjection and Model matrices
		stack.scale(glm::vec3(50));
		stack.rotate(90, glm::vec3(1, 0, 0));
		stack.translate(glm::vec3(0, 0, 1.f/50));
		
		// Send uniform data
		glUniform1i(DiffuseLocation, 0);
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(stack.top()));

		// Bind texture
		diffuseTexture.bind(GL_TEXTURE0);

		// Draw
		plane.render();

		// Unbind texture
		glActiveTexture(0);

		// Reset stack
		stack.pop();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}