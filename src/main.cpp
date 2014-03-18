#include <Project.h>

/*!
 * ValeDecem - Main function
 */
int main()
{
    int width = 1280;
    int height = 720;

	Project ourProject(width, height, "Project d'OpenGL");
	ourProject.init();
	ourProject.run();

	return EXIT_SUCCESS;
}
