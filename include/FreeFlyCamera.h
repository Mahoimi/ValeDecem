#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

/*!
* \class FreeFlyCamera
* A camera unaffected by gravity which can move freely in the 3D scene
*/
class FreeFlyCamera {
    private:

        // The position of the camera in the scene
        glm::vec3 m_Position;

        float m_fPhi;
        float m_fTheta;
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        // Compute all the parameters and angles to get the spherical coordinates of the camera
        void computeDirectionVectors(){
            m_LeftVector = glm::vec3(
                                sin(m_fPhi+(M_PI/2)),
                                0,
                                cos(m_fPhi+(M_PI/2))
                            );

            m_FrontVector = glm::vec3(
                cos(m_fTheta)*sin(m_fPhi),
                sin(m_fTheta),
                cos(m_fTheta)*cos(m_fPhi)
            );
            m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
        }

    public:
        FreeFlyCamera(){
            m_Position = glm::vec3(0,0,5);
            m_fPhi = M_PI;
            m_fTheta = 0;
            computeDirectionVectors();
        }

        explicit FreeFlyCamera(glm::vec3 position){
            m_Position = position;
            m_fPhi = M_PI;
            m_fTheta = 0;
            computeDirectionVectors();
        }

        inline void moveLeft(float t){
            m_Position += t*m_LeftVector;
        }

        inline void moveFront(float t){
            m_Position += t*m_FrontVector;
        }

        inline void moveUp(float t){
            m_Position += t*m_UpVector;
        }

        inline void rotateLeft(float degrees){
            m_fPhi += glm::radians(degrees);
            computeDirectionVectors();
        }

        inline void rotateUp(float degrees){
            m_fTheta += glm::radians(degrees);
            if((m_fTheta>M_PI/2)||(m_fTheta<-M_PI/2)){
                m_fTheta -= glm::radians(degrees);
            }
            computeDirectionVectors();
        }

        // Return the view matrix 4x4 of the camera
        inline glm::mat4 getViewMatrix() const{
            return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
        }

        // Return the position in the 3D scene of the camera
		inline const glm::vec3& getPosition() const{
			return m_Position;
        }

        // Print all the infos of the Camera instance
        void toString() {
            std::cout << "Position : " << m_Position.x << "," << m_Position.y << "," << m_Position.z << std::endl;
            std::cout << "Phi : " << m_fPhi << std::endl;
            std::cout << "Theta : " << m_fTheta << std::endl;
            std::cout << "Front : " << m_FrontVector.x << "," << m_FrontVector.y << "," << m_FrontVector.z << std::endl;
            std::cout << "Left : " << m_LeftVector.x << "," << m_LeftVector.y << "," << m_LeftVector.z << std::endl;
            std::cout << "Up : " << m_UpVector.x << "," << m_UpVector.y << "," << m_UpVector.z << std::endl;
        }
};

#endif // FREEFLYCAMERA_H
