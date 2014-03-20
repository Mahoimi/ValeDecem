#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>

/*!
* \class PointLight
* Create a Point light, a light that radiate outwards in all directions from a single point
*/
class PointLight {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	float m_Intensity;

    // We don't want an unexpected copy of an instance of this class
    PointLight(const PointLight&);
    PointLight& operator=(const PointLight&);
	
public:
	PointLight(){}
	PointLight(glm::vec3 position, glm::vec3 color, float intensity):
		m_Position(position), m_Color(color), m_Intensity(intensity) {}
	
	void init(glm::vec3 position, glm::vec3 color, float intensity){
		m_Position = position;
		m_Color = color;
		m_Intensity = intensity;
	}

    glm::vec3 & getPosition(){
		return m_Position;
	}

    glm::vec3 & getColor(){
		return m_Color;
	}

    float & getIntensity(){
		return m_Intensity;
	}

    void setPosition(glm::vec3 newPosition){
        m_Position = newPosition;
    }

	~PointLight(){}
};

#endif // POINTLIGHT_H
