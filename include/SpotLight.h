#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <glm/glm.hpp>

/*!
* \class SpotLight
*/
class SpotLight {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Color;
	float m_Intensity;

    // We don't want an unexpected copy of an instance of this class
    SpotLight(const SpotLight&);
    SpotLight& operator=(const SpotLight&);
	
public:
	SpotLight(){}
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity):
		m_Position(position), m_Direction(direction), m_Color(color), m_Intensity(intensity) {}
	
	void init(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity){
		m_Position = position;
		m_Direction = direction;
		m_Color = color;
		m_Intensity = intensity;
	}

	glm::vec3 getPosition() const{
		return m_Position;
	}

	glm::vec3 getDirection() const{
		return m_Direction;
	}

	glm::vec3 getColor() const{
		return m_Color;
	}

	float getIntensity() const{
		return m_Intensity;
	}

	~SpotLight(){}
};

#endif // SPOTLIGHT_H