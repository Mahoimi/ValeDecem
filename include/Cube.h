#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <GL/glew.h>
#include <Vertex.h>

class Cube {
private:
	unsigned int m_verticesCount;

	GLuint m_VAO;
	GLuint m_VBO[2];

	std::vector<Vertex> m_vertices;

    // We don't want an unexpected copy of an instance of this class
    Cube(const Cube& cube);
    Cube& operator=(const Cube& cube);
	void initVertices();

public:
    Cube();
	void init();
    void render() const;
	~Cube();
};

#endif // CUBE_H
