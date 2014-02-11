#include <Plane.h>

void Plane::init(){
	// Load vertex data
    m_vertices.push_back(Vertex(-1.f, -1.f, 0.0f, 0.f, 0.f, 1.f, 0.f, 1.f));
    m_vertices.push_back(Vertex(1.f, -1.f, 0.0f, 0.f, 0.f, 1.f, 1.f, 1.f));
	m_vertices.push_back(Vertex(-1.f, 1.f, 0.0f, 0.f, 0.f, 1.f, 0.f, 0.f));
    m_vertices.push_back(Vertex(1.f, 1.f, 0.0f, 0.f, 0.f, 1.f, 1.f, 0.f));

	// Index buffer data
	unsigned int index[] = {
		0, 1, 2, 2, 1, 3
	};

	// Number of duplicated vertex (= size of index)
	m_verticesCount = sizeof(index)/sizeof(unsigned int);

    // Generate 2 vertex buffer objects and 1 vertex array object
    glGenBuffers(2, m_VBO);
    glGenVertexArrays(1, &m_VAO);

	// Lock the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[0]);

	// Write the data inside the IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	// Unlock the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Lock the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);

    // Write the data inside the VBO
    // Warning ! m_vertices.data() != &m_vertices[0]
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

    // Unlock the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Lock the VAO
    glBindVertexArray(m_VAO);

        // Lock the VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, normal_coords));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tex_coords));

        // Unlock the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unlock the VAO
    glBindVertexArray(0);
}

void Plane::render() const{
    glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[0]);

        glDrawElements(GL_TRIANGLES, m_verticesCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Plane::~Plane(){
    glDeleteBuffers(2, m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}
