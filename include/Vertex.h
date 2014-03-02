#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

/*!
* \struct Vertex
* Store the informations used to describe a vertex
*/
struct Vertex{

    glm::vec3 position;
    glm::vec3 normal_coords;
    glm::vec2 tex_coords;

    Vertex(){
        for (unsigned int i = 0; i < 3 ; ++i) {
			position[i] = 0.f;
			normal_coords[i] = 0.f;
            if (i < 2) tex_coords[i] = 0.f;
		}
    }

    Vertex(GLfloat pX,GLfloat pY,GLfloat pZ,GLfloat nX,GLfloat nY,GLfloat nZ,GLfloat tX,GLfloat tY) {
		position.x=pX;
		position.y=pY;
		position.z=pZ;
		normal_coords.x=nX;
		normal_coords.y=nY;
		normal_coords.z=nZ;
		tex_coords.x=tX;
		tex_coords.y=tY;
    }

};

#endif // VERTEX_H
