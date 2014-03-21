#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


/*!
* \class SpotLight
*/
class SpotLight {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Color;
	float m_Intensity;

    glm::mat4 m_worldToLight;
    glm::mat4 m_ligthToShadowMap;
    glm::mat4 m_worldToShadowMap;

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
        setShadowMatrices();
	}

    void setShadowMatrices(){
        glm::vec3 lightUp(0.f, 1.f, 0.f);
        m_worldToLight = glm::lookAt(m_Position, m_Direction, lightUp);
        m_ligthToShadowMap = glm::perspective(60.f, 1.f, 1.f, 1000.f);
        glm::mat4 MAT4F_M1_P1_TO_P0_P1(
          0.5f, 0.f, 0.f, 0.f,
          0.f, 0.5f, 0.f, 0.f,
          0.f, 0.f, 0.5f, 0.f,
          0.5f, 0.5f, 0.5f, 1.f
        );
        // Matrice transformant une position dans l'espace du monde en projection dans l'espace de la lumière
        m_worldToShadowMap =  MAT4F_M1_P1_TO_P0_P1 * m_ligthToShadowMap * m_worldToLight;
    }

    glm::vec3& getPosition() {
		return m_Position;
	}

    glm::vec3& getDirection() {
		return m_Direction;
	}

    glm::vec3& getColor() {
		return m_Color;
	}

    float& getIntensity() {
		return m_Intensity;
	}

    void setPosition(glm::vec3 position) {
        m_Position = position;
    }

    void setDirection(glm::vec3 direction) {
        m_Direction = direction;
    }

    void setColor(glm::vec3 color) {
        m_Color = color;
    }

    void setIntensity(float intensity) {
        m_Intensity = intensity;
    }

    glm::mat4 getWorldToLight() const{
        return m_worldToLight;
    }
    glm::mat4 getLightToShadowMap() const{
        return m_ligthToShadowMap;
    }
    glm::mat4 getWorldToShadowMap() const{
        return m_worldToShadowMap;
    }

	~SpotLight(){}
};

#endif // SPOTLIGHT_H
