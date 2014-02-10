#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include <GL/glew.h>
#include <Vertex.h>

class Plane {
private:
	unsigned int m_verticesCount;

	GLuint m_VAO;
	GLuint m_VBO[2];

	std::vector<Vertex> m_vertices;

    // We don't want an unexpected copy of an instance of this class
    Plane(const Plane&);
    Plane& operator=(const Plane&);
	void initVertices();

public:
	Plane(){}
	void init();
    void render() const;
	~Plane();
};


#endif // PLANE_H