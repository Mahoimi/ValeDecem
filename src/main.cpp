#include <Project.h>

/*!
 * ValeDecem - Main function
 */
int main()
{
	int width = 800;
	int height = 600;

	Project ourProject(width, height, "Project d'OpenGL");
	ourProject.init();
	ourProject.run();

	return EXIT_SUCCESS;
}