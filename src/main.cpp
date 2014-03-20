#include <Project.h>

/*!
 * ValeDecem - Main function
 */
int main()
{
    //int width = 1280, height = 720;
    int width = 852, height = 480;

	Project ourProject(width, height, "Project d'OpenGL");
	ourProject.init();
	ourProject.run();

	return EXIT_SUCCESS;
}
