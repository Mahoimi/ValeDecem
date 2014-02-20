#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <glm/glm.hpp>

/*!
* \class DirectionalLight
*/
class DirectionalLight {
private:
	glm::vec3 m_Direction;
	glm::vec3 m_Color;
	float m_Intensity;

    // We don't want an unexpected copy of an instance of this class
    DirectionalLight(const DirectionalLight&);
    DirectionalLight& operator=(const DirectionalLight&);
	
public:
	DirectionalLight(){}
	DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity):
		m_Direction(direction), m_Color(color), m_Intensity(intensity) {}
	
	void init(glm::vec3 direction, glm::vec3 color, float intensity){
		m_Direction = direction;
		m_Color = color;
		m_Intensity = intensity;
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

	~DirectionalLight(){}
};

#endif // DIRECTIONALLIGHT_H