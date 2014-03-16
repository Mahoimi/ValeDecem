#ifndef AMBIANTLIGHT_H
#define AMBIANTLIGHT_H

#include <glm/glm.hpp>

/*!
* \class AmbiantLight
*/
class AmbiantLight {
private:
	glm::vec3 m_Color;
	float m_Intensity;

    // We don't want an unexpected copy of an instance of this class
    AmbiantLight(const AmbiantLight&);
    AmbiantLight& operator=(const AmbiantLight&);
	
public:
    AmbiantLight(){}
	
    void init(glm::vec3 color, float intensity){
		m_Color = color;
		m_Intensity = intensity;
	}

	glm::vec3 getColor() const{
		return m_Color;
	}

	float getIntensity() const{
		return m_Intensity;
	}

    ~AmbiantLight(){}
};

#endif // AMBIANTLIGHT_H
